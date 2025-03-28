
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
void dijkstra(Graph<T> * g, const int &origin, vector<int> *rn ,vector<pair<int,int>> *re) {
    // Initialize the vertices
    for(auto v : g->getVertexSet()) {
        v->setDrivingDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    //remove nodes from the iteration. If the vector is empty it does nothing.
    for(auto n : rn){
        auto v = g->findVertex(n);
        v->setVisited(true);
    }
    //remove edges from the iteration. If the vector is empty it does nothing.
    for(auto en : re){
        auto v = g->findVertex(en.first);
        for(auto e : v->getAdj()){
            if(e->getDest()==g->findVertex(en.second)){
                e->setDrivingDist(INF);
            }
        }
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
        //std::cout << "Origin not found!!" << std::endl;
        //return empty vector
        return vector<T> empty;
    }
    return res;
}

// Main function when using the driving only method
// If a vector is returned empty, it means there is no possible path for that specification
template <class T>
std::vector<vector<T>> Driving_only(Graph<T> * g, const int &origin, cont int &destination, vector<int> *rn ,vector<pair<int,int>> *re, const int $stop) {
    vector<vector<T>> res;
    vector<T> Optimal_route;
    vector<T> Alternate_route;
    int i;
    //Optimal_driving path
    dijkstra(g, origin, rn, re);
    if(stop==0){
        Optimal_route = getPath<T>(g, origin, destination);
        if(Optimal_route.empty()){
          res.push_back(Optimal_route);
          res.push_back(Optimal_route);
          return res;
        }
    }else{
        Optimal_route = getPath<T>(g, origin, stop);
        if(Optimal_route.empty()){
            res.push_back(Optimal_route);
            res.push_back(Optimal_route);
            return res;
        }
        dijkstra(g, stop, rn, re);
        vector<T> fpath = getPath<T>(g, stop, destination);
        if(fpath.empty()){
            res.push_back(fpath);
            res.push_back(fpath);
            return res;
        }
        i =0;
        for(auto v : fpath) {
            if(i==0){continue;}
            else{
                i=1;
                Optimal_route.push_back(v);
            }
        }
    }res.push_back(Optimal_route);

    i = Optimal_route.size()-1;
    for(auto v : Optimal_route){
        if(i==0 || i==Optimal_route.size()-1){
          continue;
        }
        else{
          rn.push_back(v);
        }
    }
    //Alternate_route path
    dijkstra(g, origin, rn, re);
    if(stop==0){
        Alternate_route = getPath<T>(g, origin, destination);
        if(Alternate_route.empty()){
            res.push_back(Alternate_route);
            return res;
        }
    }else{
        Alternate_route = getPath<T>(g, origin, stop);
        if(Alternate_route.empty()){
            res.push_back(Alternate_route);
            return res;
        }
        dijkstra(g, stop, rn, re);
        vector<T> spath = getPath<T>(g, stop, destination);
        if(spath.empty()){
            res.push_back(spath);
            return res;
        }
        i =0;
        for(auto v : spath) {
            if(i==0){continue;}
            else{
                i=1;
                Alternate_route.push_back(v);
            }
        }
    }res.push_back(Alternate_route);

    return res;
}



#endif //DRIVING_ONLY_H
