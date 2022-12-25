#ifndef GRAPH_H
#define GRAPH_H

#include "Headers/edge.h"
#include "Headers/node.h"

#include <QList>
#include <QString>
#include <QSet>


class Graph {

public:
    explicit Graph(bool directed, bool weighted);

    static std::pair<int, int> calcWeightRange(bool weighted);
    bool isWeighted() const;
    bool isUnweighted() const;
    bool isDirected() const;
    bool isUndirected() const;
    void clear();
    void setDirected(bool dir);

    //nodes methods
    Node* getNode(const std::string &name);
    bool hasNode(Node *node) const;
    bool hasNode(const std::string &node_name) const;
    bool addNode(Node* node);
    bool addNode(std::string node_name);
    bool removeNode(Node *node);
    bool removeNode(const std::string &name);
    bool isolateNode(Node *node);
    bool isolateNode(const std::string &name);
    bool setNodeName(Node *node, const std::string &new_name);
    bool changeNodeName(const std::string &old_name, const std::string &new_name);
    inline int countNodes() const;
    Node* randomNode();


    //edge methods
    Edge* getEdge(Node *u, Node *v);
    bool addEdge(Node *u, Node *v);
    bool addEdge(Node *u, Node *v, int w);
    bool removeEdge(Node *u, Node *v);
    bool removeEdge(const std::string &uname, const std::string &vname);
    bool hasDirectedEdge(Node *u, Node *v) const;
    bool hasEdge(Node *u, Node *v) const;
    bool setWeight(Node *u, Node *v, int w);
    inline int countEdges() const;
    int weight(Node *u, Node *v) const;
    int weight(const std::string &uname, const std::string &vname) const;
    void clearEdges();

    QList<Edge*> edgeSet();
    QList<Node*> nodeSet();

protected:
    QList<Edge*> m_edges;
    QList<Node*> m_nodes;
    const std::pair<int, int> m_weightRange;

    bool m_directed;
    bool m_weighted;

};

#endif // GRAPH_H
