#ifndef EDGE_H
#define EDGE_H

#include<map>
#include "Headers/node.h"

typedef std::map<std::pair<Node*, Node*>, int> edges;

class Edge{

public:
    Edge(std::pair<Node*, Node*>, int);

    explicit Edge(edges::iterator&);
    Node* first() const;
    Node* second() const;
    int weight() const;

    friend class Graph;

private:
    const int m_weight{};
    const std::pair<Node*, Node*> m_nodePair{};
};

#endif // EDGE_H
