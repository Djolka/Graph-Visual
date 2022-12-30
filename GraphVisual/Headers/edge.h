#ifndef EDGE_H
#define EDGE_H


#include <QVariant>


#include <map>
#include "Headers/node.h"

typedef std::map<std::pair<Node*, Node*>, int> edges;

class Edge{

public:
    Edge(std::pair<Node*, Node*>, int weight);
    Edge(const Edge *other);
    ~Edge();

    explicit Edge(edges::iterator& iter);
    Node* first() const;
    Node* second() const;
    int weight() const;
    QVariant toVariant();
    friend std::ostream &operator<<(std::ostream &os, const Edge e);

    friend class Graph;

    void setWeight(int n){m_weight=n;}


private:
    int m_weight;
    std::pair<Node*, Node*> m_nodePair;
};

#endif // EDGE_H
