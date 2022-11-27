#include "Headers/Edge.h"
#include "Headers/Node.h"

Edge::Edge(pair& node_pair, int& weight):m_weight(weight), m_node_pair(node_pair){};

Edge::Edge(edges::iterator& iter): m_weight(iter->second), m_node_pair(iter->first){};
Node* Edge::first()const{
    return m_node_pair.second;
}
Node* Edge::second() const{
    return m_node_pair.first;
}
int Edge::weight() const{
    return m_weight;
}
