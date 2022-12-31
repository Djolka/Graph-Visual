#include "Headers/graph.h"
#include <climits>
#include <algorithm>
#include <random>


Graph::Graph(bool directed, bool weighted): m_weightRange(calcWeightRange(weighted)), m_directed(directed),  m_weighted(weighted) {}

Graph::Graph(Graph &other) {
    for(const auto node : other.nodeSet()) {
        Node *n = new Node(node);
        m_nodes.append(n);
    }

    for(const auto node : other.nodeSet()) {
        Node* n = getNode(node->name());
        for(auto oldNeighbour : node->neighbours()) {
            std::string name = oldNeighbour->name();
            Node* newNeighbour = getNode(name);
            n->addNeighbour(newNeighbour);
        }
    }


    for(auto edge : other.edgeSet()) {
        Node *otherNode1 = edge->first();
        Node *otherNode2 = edge->second();

        Node *newNode1 = getNode(otherNode1->name());
        Node *newNode2 = getNode(otherNode2->name());

        std::pair<Node*, Node*> newEdge(newNode1, newNode2);

        Edge *e = new Edge(newEdge, edge->m_weight);
        m_edges.append(e);
    }


    m_weightRange.first = other.m_weightRange.first;
    m_weightRange.second = other.m_weightRange.second;

    m_directed = other.m_directed;
    m_weighted = other.m_weighted;
}

std::pair<int, int> Graph::calcWeightRange(bool weighted) {
    auto _max = weighted ? INT_MAX - 1 : 1;
    auto _min = 1;
    return {_min, _max};
}

bool Graph::isWeighted() const {
    return m_weighted;
}

bool Graph::isUnweighted() const {
    return !m_weighted;
}

bool Graph::isDirected() const {
    return m_directed;
}

bool Graph::isUndirected() const {
    return !m_directed;
}

void Graph::clear() {
    for(auto node:m_nodes){
        delete node;
    }
    for(auto edge : m_edges){
        delete edge;
    }
    m_edges.clear();
    m_nodes.clear();
}

void Graph::setDirected(bool dir) {
    m_directed = dir;
}

bool Graph::hasNode(Node *node) const {
    auto iterator = std::find_if(
      m_nodes.begin(), m_nodes.end(),
                [node](Node* x) { return x->name() == node->name();}
    );
    if (iterator != m_nodes.end()){
        return true;
    }
    return false;
}

bool Graph::hasNode(const std::string &node_name) const {
    auto iterator = std::find_if(
      m_nodes.begin(), m_nodes.end(),
                [node_name](Node* x) { return x->name() == node_name;}
    );
    if (iterator != m_nodes.end()){
        return true;
    }
    return false;
}

bool Graph::hasDirectedEdge(Node *u, Node *v) const {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if ((*it)->first() == u && (*it)->second() == v){
            return true;
        }
    }
    return false;
}

bool Graph::hasEdge(Node *u, Node *v) const {
    return m_directed ? hasDirectedEdge(u, v) : (hasDirectedEdge(u, v) || hasDirectedEdge(v, u));
}

bool Graph::addNode(Node* node){
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
    Node* n = new Node(node_name);
    return addNode(n);
}


bool Graph::removeNode(Node *node) {
    auto it = std::find(m_nodes.begin(), m_nodes.end(), node);

    if (it != m_nodes.end()){
        isolateNode(node);
        m_nodes.erase(it);
        return true;
    }
    return false;
}


bool Graph::removeNode(const std::string &name) {
    QList<Node*>::iterator it;
    for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
        if((*it)->name() == name){
            isolateNode(name);
            delete *it;
            m_nodes.erase(it);
            return true;
        }
    return false;
}


bool Graph::isolateNode(Node *node) {
    auto begin = m_edges.begin();
    auto end = m_edges.end();

    for(;begin != end; ++begin){
        if ((*begin)->first() == node || (*begin)->second() == node){
            removeEdge((*begin)->first(), (*begin)->second());
        }
    }

    return true;
}

bool Graph::isolateNode(const std::string &name) {
    QList<Node*>::iterator it;
    for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
        if((*it)->name() == name){
            isolateNode(*it);
        }

    return true;
}


bool Graph::setNodeName(Node *node, const std::string &new_name) {
    QList<Node*>::iterator it;
    for (it = m_nodes.begin(); it != m_nodes.end(); ++it){
        if((*it)->name() == node->name()){
            (*it)->setName(new_name);
            return true;
        }
    }
    return false;
}

bool Graph::changeNodeName(const std::string &old_name, const std::string &new_name) {
    QList<Node*>::iterator it;
    for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
        if((*it)->name() == old_name){
            (*it)->setName(new_name);
            return true;
        }
    return false;
}


Edge* Graph::getEdge(Node *u, Node *v) {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if ((*it)->first() == u && (*it)->second() == v){
            return *it;
        }
        if(!m_directed && (*it)->first() == v && (*it)->second() == u){
            return *it;
        }
    }
    return nullptr;
}

bool Graph::addEdge(Node *u, Node *v) {
    if(hasEdge(u,v)){
        return false;
    }
    return addEdge(u,v,1);
}

bool Graph::addEdge(Node *u, Node *v, int w) {
    if(hasEdge(u,v)){
        return false;
    }

    if(isUndirected() && (hasEdge(u,v) || hasEdge(v,u))){
        return false;
    }


    Edge *e = new Edge(std::make_pair(u,v), w);
    m_edges.append(e);

    if (m_directed) {
        u->incOutDeg();
        v->incInDeg();
    } else {
        u->incDeg();
        v->incDeg();
    }


    if(m_directed){
        u->addNeighbour(v);
    }else{
        u->addNeighbour(v);
        v->addNeighbour(u);
    }
    return true;
}

bool Graph::removeEdge(Node *u, Node *v) {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if(isUndirected()){
            if (((*it)->first() == u && (*it)->second() == v) || ((*it)->first() == v && (*it)->second() == u)){
                if(u) {
                    u->decDeg();
                    u->removeNeighbour(v);
                }

                if(v) {
                    v->decDeg();
                    v->removeNeighbour(u);
                }
                m_edges.erase(it);
                return true;
            }
        }else{
            if((*it)->first() == u && (*it)->second() == v){
                if(u) {
                    u->decOutDeg();
                    u->removeNeighbour(v);
                }

                if(v) {
                    v->decInDeg();
                }

                m_edges.erase(it);
                return true;
            }
        }
    }
    return true;
}


bool Graph::removeEdge(const std::string &uname, const std::string &vname) {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if(isUndirected()){
            if (((*it)->first()->name() == uname && (*it)->second()->name() == vname) || ((*it)->first()->name() == vname && (*it)->second()->name() == uname)){
                m_edges.erase(it);
                (*it)->first()->decDeg();
                (*it)->second()->decDeg();
                (*it)->first()->removeNeighbour((*it)->second());
                (*it)->second()->removeNeighbour((*it)->first());
                delete *it;
                return true;
            }
        }else{
            if((*it)->first()->name() == uname && (*it)->second()->name() == vname){
                (*it)->first()->decOutDeg();
                (*it)->second()->decInDeg();
                m_edges.erase(it);
                (*it)->first()->removeNeighbour((*it)->second());
                delete *it;
                return true;
            }
        }
    }
    return true;
}

bool Graph::setWeight(Node *u, Node *v, int w) {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if ((*it)->first() == u && (*it)->second() == v){
            (*it)->m_weight = w;
            return true;
        }
    }
    return false;
}

int Graph::weight(Node *u, Node *v) const {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if (((*it)->first() == u && (*it)->second() == v) || ((*it)->first() == v && (*it)->second() == u)){
            return (*it)->weight();
        }
    }
    return -1;
}

int Graph::weight(const std::string &uname, const std::string &vname) const {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if ((*it)->first()->name() == uname && (*it)->second()->name() == vname){
            return (*it)->weight();
        }
    }
    return -1;
}

void Graph::clearEdges() {
    for(auto edge: m_edges){
        delete edge;
    }
    m_edges.clear();
}


QList<Edge*> Graph::edgeSet() {
    return m_edges;
}

QList<Node*> Graph::nodeSet() {
    return m_nodes;
}

Node* Graph::randomNode() {
    int n = rand() % countNodes();
    auto it = m_nodes.begin();
    while(n > 0) {
        ++it;
        --n;
    }

    return *it;
}


Node* Graph::getNode(const std::string &name){
    for(auto n : m_nodes)
        if(n->name()==name)
            return n;
    return nullptr;
}
