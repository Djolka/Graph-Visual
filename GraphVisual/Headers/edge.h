#ifndef EDGE_H
#define EDGE_H

#include<unordered_map>
#include<map>
#include "Headers/Node.h"

typedef std::pair<Node*, Node*> nodePair;
typedef std::map<nodePair, int> edges;

class Edge{

public:
    Edge(nodePair&, int&);

    explicit Edge(edges::iterator&);
    Node* getFirst() const;
    Node* getSecond() const;
    int weight() const;

    friend class Graph;

private:
    const int &m_weight{};
    const nodePair &m_node_pair{};
};

#endif // EDGE_H
