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
    bool hasNode(Node *node) const;
    bool hasNode(const std::string &node_name) const;
    bool hasDirectedEdge(Node *u, Node *v) const;
    bool hasEdge(Node *u, Node *v) const;

    bool addNode(const Node &node);
    bool addNode(std::string node_name);
    bool removeNode(Node *node);
    bool removeNode(const std::string &name);
    //bool isolateNode(Node *node);
    //bool isolateNode(const std::string &name);
    bool setNodeName(Node *node, const std::string &new_name);
    bool changeNodeName(const std::string &old_name, const std::string &new_name);
    inline int countEdges() const;
    inline int countNodes() const;
    Edge getEdge(Node *u, Node *v);
    bool setEdge(Node *u, Node *v);
    bool setEdge(Node *u, Node *v, int w);
    //bool setEdge(const std::string &uname, const std::string &vname);
    //bool setEdge(const std::string &uname, const std::string &vname, int w);
    bool removeEdge(Node *u, Node *v);
    //bool removeEdge(const std::string &uname, const std::string &vname);
    //bool hasEdge(Node *u, Node *v) const;
    //bool hasEdge(const std::string &uname, const std::string &vname) const;
    int weight(Node *u, Node *v) const;
    //int weight(const std::string &uname, const std::string &vname) const;
    void clearEdges();
    QList<Edge> edgeSet();
    QList<Node> nodeSet();
    Node randomNode();

protected:
    QList<Edge> m_edges;
    QList<Node> m_nodes;
    const std::pair<int, int> m_weightRange;

//private:
    const bool m_directed;
    const bool m_weighted;

};

#endif // GRAPH_H
