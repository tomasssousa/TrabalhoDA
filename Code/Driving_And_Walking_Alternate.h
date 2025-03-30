///
/// @file Driving_and_Walking_Alternate.h
/// @brief Implements an environmentally-friendly route planner using driving and walking.
///
/// This module finds the shortest route combining driving and walking while adhering to user-defined constraints.
/// It ensures that:
/// - The route includes both driving and walking segments.
/// - The walking segment does not exceed the maximum allowed walking time.
/// - Parking nodes are used optimally to transition from driving to walking.
/// - If there is no solution it gives an Aproximate route
///
#ifndef DRIVING_AND_WALKING_ALTERNATE_H
#define DRIVING_AND_WALKING_ALTERNATE_H


#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "Driving_only.h"
#include "Batch_Mode_write.h"

using namespace std;

/**
* @brief This function is responsible for the edge relaxation that takes place during the Dijkstra algorithm.
* @param edge The edge to be either crossed or not.
* @return The boolean saying if the DrivingDist got changed or not.
*/
template<class T>
bool walkingrelax(Edge<T> *edge) {
    // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getWalkingDist() + edge->getWalkingWeight() < edge->getDest()->getWalkingDist()) {
        // we have found a better way to reach v
        edge->getDest()->setWalkingDist(edge->getOrig()->getWalkingDist() + edge->getWalkingWeight());
        // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

/**
* @brief Implementation of custom Dijkstra algorithm.
*
* Custom Dijkstra that takes two additional vectors and is able to avoid specific nodes and edges.
* @param g The graph to be explored.
* @param origin The id of the node from which the algorithm will start.
* @param rn The id of the nodes to be ignored.
* @param re The ids of the starting and destination vertices that define an edge to be ignored.
*/
template<class T>
void walkingdijkstra(Graph<T> *g, const int &origin, vector<int> *rn, vector<pair<int, int> > *re) {
    /// Initialize the vertices
    for (auto v: g->getVertexSet()) {
        v->setWalkingDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    ///remove nodes from the iteration. If the vector is empty it does nothing.
    if (rn != nullptr) {
        for (int n: *rn) {
            auto v = g->findVertex(n);
            if (v != nullptr) {
                v->setVisited(true);
            }
        }
    }
    ///remove edges from the iteration. If the vector is empty it does nothing.
    if (re != nullptr) {
        for (pair<int, int> en: *re) {
            auto v = g->findVertex(en.first);
            if (v != nullptr) {
                for (auto e: v->getAdj()) {
                    if (e->getDest() == g->findVertex(en.second)) {
                        e->setWalkingWeight(INF);
                    }
                }
            }
        }
    }
    auto s = g->findVertex(origin); ///< The node from which to start the algorithm.
    if (s == nullptr) {
        return;
    }
    s->setWalkingDist(0);

    MutablePriorityQueue<Vertex<T> > q; ///< PriorityQueue to be used during the algorithm.
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto e: v->getAdj()) {
            auto oldDist = e->getDest()->getWalkingDist();
            if (relax(e) && e->getDest()->isVisited() == false) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

/**
* @brief Gives the path from a node to the other, if there is one.
* @param g The graph where the nodes belong to.
* @param origin The starting node.
* @param dest The detination node.
* @return A vector with either the path from a node to the other or an empty vector in the case where there isn't a path.
*/
template<class T>
static std::vector<T> getWalkingPath(Graph<T> *g, const int &origin, const int &dest) {
    std::vector<T> res; ///< The vector where the result will be placed
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getWalkingDist() == INF) {
        // missing or disconnected
        return res;
    }
    res.push_back(v->getId());
    while (v->getPath() != nullptr) {
        v = v->getPath()->getOrig();
        res.push_back(v->getId());
    }
    reverse(res.begin(), res.end());
    if (res.empty() || res[0] != origin) {
        //std::cout << "Origin not found!!" << std::endl;
        //return empty vector
        std::vector<T> empty;
        return empty;
    }
    return res;
}

/**
 * @brief Finds valid parking nodes that allow walking to the destination within the max walking time.
 *
 * @tparam T Data type of the graph nodes.
 * @param g Pointer to the graph structure.
 * @param origin Starting node ID.
 * @param destination Target node ID.
 * @param maxWalkTime Maximum allowed walking time.
 * @return Vector containing IDs of valid parking nodes.
 */
template<class T>
vector<int> findValidParkingNodes(Graph<T> *g, int origin, int destination, int maxWalkTime) {
    vector<int> parkingNodes;
    for (auto v: g->getVertexSet()) {
        if (v->getParking() == 1 && v->getId() != origin && v->getId() != destination) {
            walkingdijkstra(g, v->getId(), {}, {});
            if (g->findVertex(destination)->getWalkingDist() <= maxWalkTime) {
                parkingNodes.push_back(v->getId());
            }
        }
    }
    return parkingNodes;
}

/**
 * @brief Computes the best driving-walking route based on user constraints.
 *
 * @tparam T Data type of the graph nodes.
 * @param g Pointer to the graph structure.
 * @param origin Starting node ID.
 * @param destination Target node ID.
 * @param maxWalkTime Maximum allowed walking time.
 * @param avoidNodes List of node IDs to avoid.
 * @param avoidEdges List of edges (pairs of node IDs) to avoid.
 * @return A vector of vectors containing:
 *         - Best driving route as a sequence of node IDs.
 *         - Chosen parking node.
 *         - Best walking route as a sequence of node IDs.
 *         - Total travel time as a string.
 */
template<class T>
vector<vector<T> > DrivingWalking(Graph<T> *g, int &origin, int &destination, int &maxWalkTime, vector<int> avoidNodes,
                                  vector<pair<int, int> > avoidEdges) {
    vector<vector<T> > bestRoute;
    vector<int> parkingNodes = findValidParkingNodes(g, origin, destination, maxWalkTime);

    if (parkingNodes.empty()) {
        writeBatchModeDrivingWalkingImpossible("../Files/output.txt", origin, destination,
                                               "There aren't any parkingNodes or the maxWalkTime was exceeded");
        return {};
        /*
        return {
            {"none"}, {"none"}, {"none"}, {"Message: There aren't any parkingNodes or the maxWalkTime was exceeded."}
        };
        */
    }

    int bestDrivingTime = INT_INF;
    int bestWalkingTime = INT_INF;
    int bestTotalTime = INT_INF;
    vector<T> bestDrivingRoute, bestWalkingRoute;
    int bestParkingNode = -1;

    for (int parkingNode: parkingNodes) {
        auto drivingRoutes = Driving_only(g, origin, parkingNode, &avoidNodes, &avoidEdges, {});
        if (drivingRoutes[0].empty()) continue;

        walkingdijkstra(g, parkingNode, {}, {});
        vector<T> walkingRoute = getWalkingPath<T>(g, parkingNode, destination);

        if (walkingRoute.empty() || g->findVertex(destination)->getWalkingDist() > maxWalkTime) continue;

        int drivingTime = g->findVertex(parkingNode)->getDrivingDist();
        int walkingTime = g->findVertex(destination)->getWalkingDist();
        int totalTime = drivingTime + walkingTime;
        if (totalTime < bestTotalTime || (totalTime == bestTotalTime && walkingRoute.size() < bestWalkingRoute.
                                          size())) {
            bestDrivingTime = drivingTime;
            bestWalkingTime = walkingTime;
            bestTotalTime = totalTime;
            bestDrivingRoute = drivingRoutes[0];
            bestWalkingRoute = walkingRoute;
            bestParkingNode = parkingNode;
        }
    }

    if (bestParkingNode == -1) {
        //writeBatchModeDrivingWalkingImpossible("../Files/output.txt", origin, destination,
        //                                       "There isn't any available route.");
        //return {};
        /*
        return {{"none"}, {"none"}, {"none"}, {"Message: There isn't any available route."}};
        */
        vector<vector<T> > bestRouteAlternate;
        vector<vector<T> > secondbestRouteAlternate;
        vector<int> parkingNodesAlternate = findValidParkingNodes(g, origin, destination, INF);
        if (parkingNodes.empty()) {
            writeBatchModeDrivingWalkingImpossible("../Files/output.txt", origin, destination,
                                                   "There aren't any parkingNodes");
            return {};
        }
        int bestDrivingTimeAlternate = INT_INF;
        int bestWalkingTimeAlternate = INT_INF;
        int bestTotalTimeAlternate = INT_INF;
        vector<T> bestDrivingRoute, bestWalkingRoute;
        int bestParkingNodeAlternate = -1;
        int SecondbestDrivingTimeAlternate = INT_INF;
        int SecondbestWalkingTimeAlternate = INT_INF;
        int SecondbestTotalTimeAlternate = INT_INF;
        vector<T> SecondbestDrivingRoute, SecondbestWalkingRoute;
        int SecondbestParkingNodeAlternate = -1;

        for (int parkingNode: parkingNodes) {
            auto drivingRoutesAlternate = Driving_only(g, origin, parkingNode, &avoidNodes, &avoidEdges, {});
            if (drivingRoutesAlternate[0].empty()) continue;

            walkingdijkstra(g, parkingNode, {}, {});
            vector<T> walkingRouteAlternate = getWalkingPath<T>(g, parkingNode, destination);

            if (walkingRouteAlternate.empty()) continue;

            int drivingTimeAlternate = g->findVertex(parkingNode)->getDrivingDist();
            int walkingTimeAlternate = g->findVertex(destination)->getWalkingDist();
            int totalTimeAlternate = drivingTime + walkingTime;
            if (totalTimeAlternate < bestTotalTimeAlternate || (totalTimeAlternate == bestTotalTimeAlternate && walkingRouteAlternate.size() < bestWalkingRouteAlternate.size())) {
                SecondbestDrivingTimeAlternate = bestDrivingTimeAlternate;
                SecondbestWalkingTimeAlternate = bestWalkingTimeAlternate;
                SecondbestTotalTimeAlternate = bestTotalTimeAlternate;
                SecondbestDrivingRouteAlternate = bestDrivingRouteAlternate;
                SecondbestWalkingRouteAlternate = bestWalkingRouteAlternate;
                SecondbestParkingNodeAlternate = bestParkingNodeAlternate;
                bestDrivingTimeAlternate = drivingTimeAlternate;
                bestWalkingTimeAlternate = walkingTimeAlternate;
                bestTotalTimeAlternate = totalTimeAlternate;
                bestDrivingRouteAlternate = drivingRoutes[0]Alternate;
                bestWalkingRouteAlternate = walkingRouteAlternate;
                bestParkingNodeAlternate = parkingNodeAlternate;
            }
            else if (totalTimeAlternate < SecondbestTotalTimeAlternate || (totalTimeAlternate == SecondbestTotalTimeAlternate && walkingRouteAlternate.size() < SecondbestWalkingRouteAlternate.size())){
                bestDrivingTimeAlternate = drivingTimeAlternate;
                bestWalkingTimeAlternate = walkingTimeAlternate;
                bestTotalTimeAlternate = totalTimeAlternate;
                bestDrivingRouteAlternate = drivingRoutes[0]Alternate;
                bestWalkingRouteAlternate = walkingRouteAlternate;
                bestParkingNodeAlternate = parkingNodeAlternate;
            }
        }

        if (bestParkingNode == -1) {
            writeBatchModeDrivingWalkingImpossible("../Files/output.txt", origin, destination,
                                                "There isn't any available route.");
            return {};
        }
        writeBatchModeDrivingWalking("../Files/output.txt", origin, destination, bestDrivingRouteAlternate, bestDrivingTimeAlternate,
                                 bestParkingNodeAlternate, bestWalkingRouteAlternate, bestWalkingTimeAlternate, bestTotalTimeAlternate);
        if (SecondbestParkingNodeAlternate == -1) {
            writeBatchModeDrivingWalkingImpossible("../Files/output.txt", origin, destination,
                                                "There isn't any available route.");
            return {};
        }
        writeBatchModeDrivingWalking("../Files/output.txt", origin, destination, SecondbestDrivingRouteAlternate, SecondbestDrivingTimeAlternate,
                                 SecondbestParkingNodeAlternate, SecondbestWalkingRouteAlternate, SecondbestWalkingTimeAlternate, SecondbestTotalTimeAlternate);
        return {};

    }
    else{
    writeBatchModeDrivingWalking("../Files/output.txt", origin, destination, bestDrivingRoute, bestDrivingTime,
                                 bestParkingNode, bestWalkingRoute, bestWalkingTime, bestTotalTime);
    return {};
    /*
    return {bestDrivingRoute, {bestParkingNode}, bestWalkingRoute, {to_string(bestTotalTime)}};
    */
    }
}


#endif //DRIVING_AND_WALKING_ALTERNATE_H
