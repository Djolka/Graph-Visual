#include "edge.h"
#include "node.h"

Edge::Edge(std::pair<Node *, Node *> nodePair, int weight)
    : m_weight(weight), m_nodePair(nodePair) {}

Node *Edge::first() const { return m_nodePair.first; }

Node *Edge::second() const { return m_nodePair.second; }

int Edge::weight() const { return m_weight; }

QVariant Edge::toVariant() {
    QVariantMap map;
    QString nodeName = QString::fromStdString(m_nodePair.first->name());
    map.insert("node1", nodeName);

    nodeName = QString::fromStdString(m_nodePair.second->name());
    map.insert("node2", nodeName);

    int nodeWeight = weight();
    map.insert("weight", nodeWeight);

    return map;
}
