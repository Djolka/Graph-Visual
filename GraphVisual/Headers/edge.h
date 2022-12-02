#ifndef EDGE_H
#define EDGE_H

#include <map>
#include "Headers/node.h"

typedef std::map<std::pair<Node*, Node*>, int> edges;

class Edge{

public:
    Edge(std::pair<Node*, Node*> nodePair, int weight);

    explicit Edge(edges::iterator& iter);
    Node* first() const;
    Node* second() const;
    int weight() const;

    bool operator==(const pair(m_node_pair)) const;

    friend class Graph;
    friend std::ostream &operator<<(std::ostream &os, const Edge e);

private:
    int m_weight;
    const std::pair<Node*, Node*> m_nodePair{};
};

#endif // EDGE_H
