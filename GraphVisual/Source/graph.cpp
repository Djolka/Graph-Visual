#include "Headers/graph.h"
#include <climits>
#include <algorithm>
#include <random>


Graph::Graph(bool directed, bool weighted): m_weightRange(calcWeightRange(weighted)), m_directed(directed),  m_weighted(weighted) {}

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
//    da bi se dodavali nodovi na click koji su istog imena
//    if (hasNode(node->name())){
//        return false;
//    }
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

    if (it != m_nodes.end()){ // ovde it nije konst
        isolateNode(node);
        m_nodes.erase(it);    // ovde ga konvertuje u const
        return true;
    }
    return false;
}


bool Graph::removeNode(const std::string &name) {
    QList<Node*>::iterator it;
    for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
        if((*it)->name() == name){
            isolateNode(name);
            delete *it;          // TOFIX
            m_nodes.erase(it);
            return true;
        }
    return false;
}

// zasto nam je ovo bool ako nikad ne vraca false -> sto nije void?
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

int Graph::countEdges() const {
    return m_edges.size();
}

int Graph::countNodes() const {
    return m_nodes.size();
}

//TOCHECK(some cases)
bool Graph::setEdge(Node *u, Node *v, int w){
    if (w < m_weightRange.first || w > m_weightRange.second){
        return false;
    }

    if(u == v || !hasNode(u) || !hasNode(v)){
        return false;
    }

    if(hasDirectedEdge(u,v)){
        auto it = m_edges.begin();
        for(;it != m_edges.end(); ++it){
            if ((*it)->first() == u && (*it)->second() == v){
                m_edges.erase(it);
            }
        }
        Edge* e = new Edge(std::make_pair(u,v), w);
        m_edges.append(e);
        return true;
    }

    if(!m_directed && hasDirectedEdge(v,u)){
        auto it = m_edges.begin();
        for(;it != m_edges.end(); ++it){
            if ((*it)->first() == v && (*it)->second() == u){
                m_edges.erase(it);
            }
        }
        Edge* e = new Edge(std::make_pair(v,u), w);
        m_edges.append(e);
        return true;
    }

    addEdge(u,v,w);
    return true;
}


bool Graph::setEdge(Node *u, Node *v) {
    return setEdge(u, v, 1);
}


bool Graph::setEdge(const std::string &uname, const std::string &vname) {
    Node *u = new Node(uname);
    Node *v = new Node(vname);
    return setEdge(u, v, 1);
}

bool Graph::setEdge(const std::string &uname, const std::string &vname, int w) {
    Node *u = new Node(uname);
    Node *v = new Node(vname);
    return setEdge(u, v, w);
}


Edge* Graph::getEdge(Node *u, Node *v) {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if ((*it)->first() == u && (*it)->second() == v){
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

    // da li treba ovo da se brise?
    Edge *e = new Edge(std::make_pair(u,v), w);
    m_edges.append(e);
//    m_edges.insert(m_edges.size(), e);
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

//That means that if your code is not calling abort directly nor sending itself the SIGABRT signal via raise,
//and you don't have any failing assertions, the cause must be that a support library (which could be libc) has encountered an internal error.
//pa ok...........
bool Graph::removeEdge(Node *u, Node *v) {
    auto it = m_edges.begin();
    for(;it != m_edges.end(); ++it){
        if(isUndirected()){
            // ovde postoje grane (u, v) i (v, u) ili samo jedna od njih?
            // jer ako postoje obe onda nema svrhe proveavati oba uslova
            if (((*it)->first() == u && (*it)->second() == v) || ((*it)->first() == v && (*it)->second() == u)){
                // ako nisu nullptr/invalidated
                if(u) {
                    u->decDeg();
                    u->removeNeighbour(v);
                }

                if(v) {
                    v->decDeg();
                    v->removeNeighbour(u);
                }


// erase(it) erases the iterator, and hence also the element pointing by it,
// vector::erase destroys the removed object, which involves calling its destructor
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
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_nodes.begin(), m_nodes.end(), g);
    Node* n = m_nodes.takeFirst();

    return n;
}

Node* Graph::getNode(std::string name){
    for(auto n : m_nodes)
        if(n->name()==name)
            return n;
    return nullptr;
}



//void Graph::clearNodes() {
//    for(auto node: m_nodes){
//        removeNode(node);
//        delete node;
//    }
//    m_nodes.clear();
//}










