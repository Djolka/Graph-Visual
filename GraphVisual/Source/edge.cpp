#include "Headers/edge.h"
#include "Headers/node.h"


Edge::Edge(std::pair<Node*, Node*> nodePair, int weight):m_weight(weight), m_nodePair(nodePair){}

Edge::Edge(edges::iterator& iter): m_weight(iter->second), m_nodePair(iter->first){}
Node* Edge::first()const{
    return m_nodePair.first;
}
Node* Edge::second() const{
    return m_nodePair.second;
}
int Edge::weight() const{
    return m_weight;
}

std::ostream &operator<<(std::ostream &os, const Edge &e){
    os<<e.first()->name()<<" "<<e.weight()<<std::endl;
    return os;
}
