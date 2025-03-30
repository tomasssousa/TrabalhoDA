
#ifndef DRIVING_ONLY_H
#define DRIVING_ONLY_H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "Batch_Mode_write.h"

using namespace std;
/**
* @brief This function is responsible for the edge relaxation that takes place during the Dijkstra algorithm.
* @param edge The edge to be either crossed or not.
* @return The boolean saying if the DrivingDist got changed or not.
*/
template<class T>
bool relax(Edge<T> *edge) {
    // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDrivingDist() + edge->getDrivingWeight() < edge->getDest()->getDrivingDist()) {
        // we have found a better way to reach v
        edge->getDest()->setDrivingDist(edge->getOrig()->getDrivingDist() + edge->getDrivingWeight());
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
void dijkstra(Graph<T> *g, const int &origin, vector<int> *rn, vector<pair<int, int> > *re) {
    /// Initialize the vertices
    for (auto v: g->getVertexSet()) {
        v->setDrivingDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    ///remove nodes from the iteration. If the vector is empty it does nothing.
    for (int n: *rn) {
        auto v = g->findVertex(n);
        v->setVisited(true);
    }
    ///remove edges from the iteration. If the vector is empty it does nothing.
    for (pair<int, int> en: *re) {
        auto v = g->findVertex(en.first);
        for (auto e: v->getAdj()) {
            if (e->getDest() == g->findVertex(en.second)) {
                e->setDrivingWeight(INF);
            }
        }
    }
    auto s = g->findVertex(origin); ///< The node from which to start the algorithm.
    s->setDrivingDist(0);

    MutablePriorityQueue<Vertex<T> > q; ///< PriorityQueue to be used during the algorithm.
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto e: v->getAdj()) {
            auto oldDist = e->getDest()->getDrivingDist();
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
static std::vector<T> getPath(Graph<T> *g, const int &origin, const int &dest) {
    std::vector<T> res; ///< The vector where the result will be placed
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDrivingDist() == INF) {
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
* @brief Main function when using the driving only method.
*
* @param g The graph to use.
* @param origin The id of the starting node.
* @param destination The id of the destination node.
* @param rn The id of the nodes to be ignored.
* @param re The ids of the starting and destination vertices that define an edge to be ignored.
* @param stop The id of the node to include in the path.
* @return The Vectors with the Optimal path and the alterante route, respectively. If a vector is returned empty, it means there is no possible path for that .
*/
template<class T>
//!In the case where both avoidNodes and avoidSegments and stop are not provided, they will have default values
std::vector<vector<T> > Driving_only(Graph<T> *g, const int &origin, const int &destination, vector<int> *rn = nullptr,
                                     vector<pair<int, int> > *re = nullptr, const int &stop = 0) {
    vector<vector<T> > res; ///< Vector that will have the Optimal and Alternate routes.
    vector<T> Optimal_route;
    vector<T> Alternate_route;
    int i; ///< Value to be used for counting.
    ///Optimal_driving path.
    dijkstra(g, origin, rn, re);
    if (stop == 0) {
        /// Verify if there is a stop to be made.
        Optimal_route = getPath<T>(g, origin, destination); /// Get the full path.
        if (Optimal_route.empty()) {
            res.push_back(Optimal_route);
            res.push_back(Optimal_route);
            return res;
        }
    } else {
        Optimal_route = getPath<T>(g, origin, stop); /// Get the path to the stop.
        if (Optimal_route.empty()) {
            res.push_back(Optimal_route);
            res.push_back(Optimal_route);
            return res;
        }
        dijkstra(g, stop, rn, re);
        vector<T> fpath = getPath<T>(g, stop, destination); /// Get the path from the stop to the destination.
        if (fpath.empty()) {
            res.push_back(fpath);
            res.push_back(fpath);
            return res;
        }
        i = 0;
        for (auto v: fpath) {
            if (i == 0) {
                i = 1;
            } else {
                Optimal_route.push_back(v); /// Add the two parts of the path.
            }
        }
    }
    res.push_back(Optimal_route); ///Store the path.
    ///Alternate_route preparation.
    i = Optimal_route.size() - 1;
    for (auto v: Optimal_route) {
        if (i == 0 || i == Optimal_route.size() - 1) {
        } else {
            rn->push_back(v);
            /// Prepare the alternate route adding the used nodes grom the optimal route to the vector of nodes to ignore.
        }
        i--;
    }
    ///Alternate_route path. The process will be identical the the Optimal_driving path, simply with more nodes to ignore.
    dijkstra(g, origin, rn, re);
    if (stop == 0) {
        Alternate_route = getPath<T>(g, origin, destination);
        if (Alternate_route.empty()) {
            res.push_back(Alternate_route);
            return res;
        }
    } else {
        Alternate_route = getPath<T>(g, origin, stop);
        if (Alternate_route.empty()) {
            res.push_back(Alternate_route);
            return res;
        }
        dijkstra(g, stop, rn, re);
        vector<T> spath = getPath<T>(g, stop, destination);
        if (spath.empty()) {
            res.push_back(spath);
            return res;
        }
        i = 0;
        for (auto v: spath) {
            if (i == 0) {
                i = 1;
            } else {
                Alternate_route.push_back(v);
            }
        }
    }
    res.push_back(Alternate_route);

    return res;
}


#endif //DRIVING_ONLY_H
