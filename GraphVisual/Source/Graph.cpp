#include "Headers/graph.h"
#include <algorithm>
#include <random>


Graph::Graph(bool directed, bool weighted): m_weightRange(calcWeightRange(weighted)), _directed(directed),  _weighted(weighted) {}

std::pair<int, int> Graph::calcWeightRange(bool weighted) {
    auto _max = weighted ? INT_MAX - 1 : 1;
    auto _min = 1;
    return {_min, _max};
}

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

void Graph::clear() {
    m_edges.clear();
    m_nodes.clear();
}

bool Graph::hasNode(Node *node) const {
    auto iterator = std::find_if(
      m_nodes.begin(), m_nodes.end(),
                [&node](Node x) { return x.name() == node->name();}
    );
    if (iterator != m_nodes.end()){
        return true;
    }
    return false;
}

bool Graph::hasNode(const std::string &node_name) const {
    auto iterator = std::find_if(
      m_nodes.begin(), m_nodes.end(),
                [node_name](Node x) { return x.name() == node_name;}
    );
    if (iterator != m_nodes.end()){
        return true;
    }
    return false;
}

//TOCHECK
bool Graph::hasDirectedEdge(Node *u, Node *v) const {

    auto begin = m_edges.begin();
    auto end = m_edges.end();
    auto index = m_edges.indexOf(std::make_pair(u, v));

    if (end-begin > index){
        return false;
    }
    return true;
}

//TOCHECK
bool Graph::hasEdge(Node *u, Node *v) const {
     return _directed ? hasDirectedEdge(u, v) : (hasDirectedEdge(u, v) || hasDirectedEdge(v, u));
}


bool Graph::addNode(const Node &node) {
    if (hasNode(node.name())){
        return false;
    }
    m_nodes.append(node);
    return true;
}

bool Graph::addNode(std::string node_name) {
    if (node_name.empty()){
        return false;
    }
    if (hasNode(node_name)){
        return false;
    }
    return addNode(Node(node_name));
}

//TOCHECK
//bool Graph::setEdge(Node *u, Node *v) {
//    return setEdge(u, v, 1);
//}

//TODO
//bool Graph::setEdge(Node *u, Node *v, int w){}

//TOCHECK
//Edge Graph::getEdge(Node *u, Node *v) {
//    auto it = std::find(m_edges.begin(), m_edges.end(), std::pair(u,v));
//    if(it != m_edges.end()){
//        return *it;
//    }
//    (what is return for failure?)
//    return *it;
//}

//TOCHECK
bool Graph::removeEdge(Node *u, Node *v) {
    auto it = std::find(m_edges.begin(), m_edges.end(), std::pair(u,v));
    if(it != m_edges.end()){
        m_edges.removeAt(it-m_edges.begin());
        return true;
    }
    return false;
}

//TOCHECK
int Graph::weight(Node *u, Node *v) const {
    auto it = std::find(m_edges.begin(), m_edges.end(), std::pair(u,v));

    if(it != m_edges.end()){
        return it->weight();
    }
    return -1;
}


QList<Edge> Graph::edgeSet() {
    return m_edges;
}

QList<Node> Graph::nodeSet() {
    return m_nodes;
}

Node Graph::randomNode() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_nodes.begin(), m_nodes.end(), g);
    Node n = m_nodes.takeFirst();

    return n;
}











