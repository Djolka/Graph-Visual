#include "Headers/graph.h"


bool Graph::isWeighted() const {
    return _weighted;
}

bool Graph::isUnweighted() const {
    return !_weighted;
}

bool Graph::isDirected() const {
    return _directed;
}

bool Graph::isUndirected() const {
    return !_directed;
}



bool Graph::removeEdge(Node *u, Node *v){
    return true;
}
int Graph::weight(Node u, Node v) const{
    return 0;
}
QList<Edge> Graph::edges(){
    return m_edges;
}
QList<Node> Graph::nodes(){
    return m_nodes;
}
Node Graph::randomNode(){
    return m_nodes[0];
}
Edge* Graph::getEdge(Node a, Node b){
    return &m_edges[0];
}
