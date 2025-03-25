
#ifndef DRIVING_ONLY_H
#define DRIVING_ONLY_H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"

using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDrivingDist() + edge->getDrivingWeight() < edge->getDest()->getDrivingDist()) { // we have found a better way to reach v
        edge->getDest()->setDrivingDist(edge->getOrig()->getDrivingDist() + edge->getDrivingWeight()); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {
    // Initialize the vertices
    for(auto v : g->getVertexSet()) {
        v->setDrivingDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    auto s = g->findVertex(origin);
    s->setDrivingDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto e : v->getAdj()) {
            auto oldDist = e->getDest()->getDrivingDist();
            if (relax(e) && e->getDest()->isVisited()==false){
                if (oldDist == INF) {
                    q.insert(e->getDest());
                }
                else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

template <class T>
static std::vector<T> getPath(Graph<T> * g, const int &origin, const int &dest) {
    std::vector<T> res;
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INF) { // missing or disconnected
        return res;
    }
    res.push_back(v->getInfo());
    while(v->getPath() != nullptr) {
        v = v->getPath()->getOrig();
        res.push_back(v->getInfo());
    }
    reverse(res.begin(), res.end());
    if(res.empty() || res[0] != origin) {
        std::cout << "Origin not found!!" << std::endl;
    }
    return res;
}
#endif //DRIVING_ONLY_H
