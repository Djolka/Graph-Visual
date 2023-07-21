#include "graph.h"
#include <algorithm>
#include <climits>
#include <random>

Graph::Graph(bool directed)
        : m_directed(directed) {}

Graph::Graph(Graph &other) {
    for (const auto node : other.nodeSet()) {
        Node *n = new Node(node);
        m_nodes.append(n);
    }

    for (const auto node : other.nodeSet()) {
        Node *n = getNode(node->name());
        for (auto oldNeighbour : node->neighbours()) {
            std::string name = oldNeighbour->name();
            Node *newNeighbour = getNode(name);
            n->addNeighbour(newNeighbour);
        }
    }

    for (auto edge : other.edgeSet()) {
        Node *otherNode1 = edge->first();
        Node *otherNode2 = edge->second();

        Node *newNode1 = getNode(otherNode1->name());
        Node *newNode2 = getNode(otherNode2->name());

        std::pair<Node *, Node *> newEdge(newNode1, newNode2);

        Edge *e = new Edge(newEdge, edge->m_weight);
        m_edges.append(e);
    }

    m_directed = other.m_directed;
}

bool Graph::isDirected() const { return m_directed; }

bool Graph::isUndirected() const { return !m_directed; }

void Graph::setDirected(bool dir) { m_directed = dir; }

bool Graph::hasNode(const std::string &node_name) const {
    auto iterator =
            std::find_if(m_nodes.begin(), m_nodes.end(),
                                     [node_name](Node *x) { return x->name() == node_name; });
    if (iterator != m_nodes.end()) {
        return true;
    }
    return false;
}

bool Graph::hasDirectedEdge(Node *u, Node *v) const {
    auto it = m_edges.begin();
    for (; it != m_edges.end(); ++it) {
        if ((*it)->first() == u && (*it)->second() == v) {
            return true;
        }
    }
    return false;
}

bool Graph::hasEdge(Node *u, Node *v) const {
    return m_directed ? hasDirectedEdge(u, v)
                                        : (hasDirectedEdge(u, v) || hasDirectedEdge(v, u));
}

bool Graph::addNode(Node *node) {
    m_nodes.append(node);
    return true;
}

bool Graph::removeNode(Node *node) {
    QList<Node *>::iterator it = std::find(m_nodes.begin(), m_nodes.end(), node);

    if (it != m_nodes.end()) {
        isolateNode(node);
        m_nodes.erase(it);
        return true;
    }
    return false;
}

bool Graph::isolateNode(Node *node) {
    auto begin = m_edges.begin();
    auto end = m_edges.end();

    for (; begin != end; ++begin) {
        if ((*begin)->first() == node || (*begin)->second() == node) {
            removeEdge((*begin)->first(), (*begin)->second());
        }
    }

    return true;
}

Edge *Graph::getEdge(Node *u, Node *v) {
    auto it = m_edges.begin();
    for (; it != m_edges.end(); ++it) {
        if ((*it)->first() == u && (*it)->second() == v) {
            return *it;
        }
        if (!m_directed && (*it)->first() == v && (*it)->second() == u) {
            return *it;
        }
    }
    return nullptr;
}

bool Graph::addEdge(Node *u, Node *v, int w) {
    if (hasEdge(u, v)) {
        return false;
    }

    if (isUndirected() && (hasEdge(u, v) || hasEdge(v, u))) {
        return false;
    }

    Edge *e = new Edge(std::make_pair(u, v), w);
    m_edges.append(e);

    if (m_directed) {
        u->incOutDeg();
        v->incInDeg();
    } else {
        u->incDeg();
        v->incDeg();
    }

    if (m_directed) {
        u->addNeighbour(v);
    } else {
        u->addNeighbour(v);
        v->addNeighbour(u);
    }
    return true;
}

bool Graph::removeEdge(Node *u, Node *v) {
    auto it = m_edges.begin();
    for (; it != m_edges.end(); ++it) {
        if (isUndirected()) {
            if (((*it)->first() == u && (*it)->second() == v) ||
                    ((*it)->first() == v && (*it)->second() == u)) {
                u->decDeg();
                v->decDeg();
                u->removeNeighbour(v);
                v->removeNeighbour(u);
                delete *it;
                (*it)->m_nodePair.first = u;
                (*it)->m_nodePair.second = v;
                m_edges.erase(it);
                return true;
            }
        } else {
            if ((*it)->first() == u && (*it)->second() == v) {
                u->decOutDeg();
                v->decInDeg();
                u->removeNeighbour(v);
                delete *it;
                (*it)->m_nodePair.first = u;
                (*it)->m_nodePair.second = v;
                m_edges.erase(it);
                return true;
            }
        }
    }
    return true;
}

int Graph::weight(Node *u, Node *v) const {
    auto it = m_edges.begin();
    for (; it != m_edges.end(); ++it) {
        if (((*it)->first() == u && (*it)->second() == v) ||
                ((*it)->first() == v && (*it)->second() == u)) {
            return (*it)->weight();
        }
    }
    return -1;
}

QList<Edge *> Graph::edgeSet() { return m_edges; }

QList<Node *> Graph::nodeSet() { return m_nodes; }

Node *Graph::randomNode() {
    int n = rand() % countNodes();
    auto it = m_nodes.begin();
    while (n > 0) {
        ++it;
        --n;
    }

    return *it;
}

Node *Graph::getNode(const std::string &name) {
    for (auto n : m_nodes)
        if (n->name() == name)
            return n;
    return nullptr;
}
