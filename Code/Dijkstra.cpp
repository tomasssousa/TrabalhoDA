#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"

using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    // TODO
    if (edge->getOrig()->getDist() + edge->getWeight() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;

}

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {
    // TODO

    MutablePriorityQueue<Vertex<T>> MPQ;
    for (Vertex<T> *v : g->getVertexSet()) {
        v->setPath(nullptr);
        v->setDist(INF);
        v->setVisited(false);
        //if (v==g->findVertex(origin)) {v->setDist(0);}
        MPQ.insert(v);
    }

    Vertex<T> *v = g->findVertex(origin);
    v->setDist(0);
    MPQ.decreaseKey(v);
    //MPQ.insert(v);

    while (MPQ.empty() == false) {
        Vertex<T> *u = MPQ.extractMin();
        u->setVisited(true);
        for (Edge<T> *a : u->getAdj()) {
            Vertex<T> *w = a->getDest();
            auto oldDIST= w->getDist();
            if (w->isVisited()==false && relax(a)) {
                //if (oldDIST==INF){MPQ.insert(w);}
                //else{MPQ.decreaseKey(w);}
                MPQ.decreaseKey(w);
            }
        }
    }

}

template <class T>
static std::vector<T> getPath(Graph<T> * g, const int &origin, const int &dest) {
    std::vector<T> res;
    // TODO
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