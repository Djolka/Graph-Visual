#ifndef EDGE_H
#define EDGE_H

#include <map>
#include "Headers/node.h"

typedef std::pair<Node*, Node*> pair;
typedef std::map<pair, int> edges;

class Edge{

public:
    Edge(pair&, int&);

    explicit Edge(edges::iterator&);
    Node* first() const;
    Node* second() const;
    int weight() const;

    bool operator==(const pair(m_node_pair)) const;

    friend class Graph;

private:
    const int &m_weight{};
    const pair &m_node_pair{};
};

#endif // EDGE_H
