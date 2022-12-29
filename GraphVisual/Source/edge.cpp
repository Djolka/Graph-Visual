#include "Headers/edge.h"
#include "Headers/node.h"

Edge::Edge(std::pair<Node*, Node*> nodePair, int weight):m_weight(weight), m_nodePair(nodePair){}

Edge::Edge(const Edge *other) {
    m_weight = other->m_weight;
    Node *n1 = new Node(other->m_nodePair.first);
    Node *n2 = new Node(other->m_nodePair.second);
    m_nodePair = std::pair<Node*, Node*>(n1, n2);
}

Edge::Edge(edges::iterator& iter): m_weight(iter->second), m_nodePair(iter->first){}

Edge::~Edge() {
    delete m_nodePair.first;
    delete m_nodePair.second;
}

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
    os << e.first()->name() << " " << e.second()->name() << e.weight() << std::endl;
    return os;
}
