#include "node.h"
#include <QPointF>
#include <cmath>
#include <utility>

Node::Node(const Node *other) {
    m_inDeg = other->inDeg();
    m_outDeg = other->outDeg();
    m_deg = other->m_deg;
    m_name = other->m_name;
    m_position = other->m_position;
}

Node::Node(std::string name) {
    m_inDeg = 0;
    m_outDeg = 0;
    m_deg = 0;
    m_name = name;
    m_position = QPointF(0, 0);
}

unsigned Node::inDeg() const { return m_inDeg; }

unsigned Node::outDeg() const { return m_outDeg; }

unsigned Node::deg() const { return m_deg; }

QPointF Node::position() const { return m_position; }

std::string Node::name() const { return m_name; }

bool Node::operator==(const Node &second) const {
    return m_name == second.m_name;
}

bool Node::operator<(const Node &second) const {
    int res = m_name.compare(second.m_name);

    if (res < 0)
        return true;
    else
        return false;
}

bool Node::removeNeighbour(Node *n) {
    QList<Node *>::iterator it =
            std::find(m_neighbours.begin(), m_neighbours.end(), n);
    if (it != m_neighbours.end()) {
        m_neighbours.erase(it);
        return true;
    }
    return false;
}

QList<Node *> Node::neighbours() { return m_neighbours; }

bool Node::addNeighbour(Node *n) {
    auto it = std::find(m_neighbours.begin(), m_neighbours.end(), n);
    if (it == m_neighbours.end()) {
        m_neighbours.append(n);
        return true;
    }
    return false;
}

void Node::incInDeg() { m_inDeg++; }

void Node::incOutDeg() { m_outDeg++; }

void Node::decInDeg() {
    if (m_inDeg > 0) { m_inDeg--; }
}

void Node::decOutDeg() {
    if (m_outDeg > 0) { m_outDeg--; }
}

void Node::incDeg() { m_deg++; }

void Node::decDeg() {
    if (m_deg > 0) { m_deg--; }
}

//std::ostream &operator<<(std::ostream &os, const Node &n) {
//    os << n.name() << " " << n.inDeg() << " " << n.outDeg() << " " << n.deg() << std::endl;
//    return os;
//}
