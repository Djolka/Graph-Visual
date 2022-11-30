#include "Headers/edge.h"
#include "Headers/node.h"

Edge::Edge(pair& node_pair, int& weight):m_weight(weight), m_node_pair(node_pair){}

Edge::Edge(edges::iterator& iter): m_weight(iter->second), m_node_pair(iter->first){}

Node* Edge::first()const{
    return m_node_pair.first;
}
Node* Edge::second() const{
    return m_node_pair.second;
}
int Edge::weight() const{
    return m_weight;
}

bool Edge::operator==(const pair(m_node_pair)) const{
    return (this->first()->name() == m_node_pair.first->name()) && (this->second()->name() == m_node_pair.second->name());
}
