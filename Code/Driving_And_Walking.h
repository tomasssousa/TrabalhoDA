/// 
/// @file Driving_and_Walking.h
/// @brief Implements an environmentally-friendly route planner using driving and walking.
///
/// This module finds the shortest route combining driving and walking while adhering to user-defined constraints.
/// It ensures that:
/// - The route includes both driving and walking segments.
/// - The walking segment does not exceed the maximum allowed walking time.
/// - Parking nodes are used optimally to transition from driving to walking.
///
#ifndef DRIVING_AND_WALKING_H
#define DRIVING_AND_WALKING_H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "Driving_only.h"

using namespace std;

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
template <class T>
vector<int> findValidParkingNodes(Graph<T> *g, int origin, int destination, int maxWalkTime) {
    vector<int> parkingNodes;
    for (auto v : g->getVertexSet()) {
        if (v->getParking() == 1 && v->getId() != origin && v->getId() != destination) {
            dijkstra(g, v->getId(), {}, {});
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
template <class T>
vector<vector<T>> DrivingWalking(Graph<T> *g, int origin, int destination, int maxWalkTime, vector<int> avoidNodes, vector<pair<int, int>> avoidEdges) {
    vector<vector<T>> bestRoute;
    vector<int> parkingNodes = findValidParkingNodes(g, origin, destination, maxWalkTime);

    if (parkingNodes.empty()) {
        return { {"none"}, {"none"}, {"none"}, {"Message: There aren't any parkingNodes or the maxWalkTime was exceeded."} };
    }

    int bestTotalTime = INF;
    vector<T> bestDrivingRoute, bestWalkingRoute;
    int bestParkingNode = -1;

    for (int parkingNode : parkingNodes) {
        auto drivingRoutes = Driving_only(g, origin, parkingNode, &avoidNodes, &avoidEdges, {});
        if (drivingRoutes[0].empty()) continue;

        dijkstra(g, parkingNode, {}, {});
        vector<T> walkingRoute = getPath<T>(g, parkingNode, destination);

        if (walkingRoute.empty() || g->findVertex(destination)->getWalkingDist() > maxWalkTime) continue;

        int totalTime = g->findVertex(parkingNode)->getDrivingDist() + g->findVertex(destination)->getWalkingDist();
        if (totalTime < bestTotalTime || (totalTime == bestTotalTime && walkingRoute.size() < bestWalkingRoute.size())) {
            bestTotalTime = totalTime;
            bestDrivingRoute = drivingRoutes[0];
            bestWalkingRoute = walkingRoute;
            bestParkingNode = parkingNode;
        }
    }

    if (bestParkingNode == -1) {
        return { {"none"}, {"none"}, {"none"}, {"Message: There isn't any available route."} };
    }

    return { bestDrivingRoute, {bestParkingNode}, bestWalkingRoute, {to_string(bestTotalTime)} };
}

#endif //DRIVING_AND_WALKING_H
