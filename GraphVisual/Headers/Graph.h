#ifndef GRAPH_H
#define GRAPH_H

//#include "Headers/Edge.h"
#include "Headers/Node.h"

#include <QList>
#include <QString>
#include <QSet>


class Graph {

public:
    Graph(bool directed, bool weighted);

    bool isWeighted() const;
    bool isUnweighted() const;
    bool isDirected() const;
    bool isUndirected() const;
    //void clear();
    //bool hasNode(Node *node) const;
    //bool hasNode(const std::string &node_name) const;
    //bool hasEdge(Edge *edge) const;
    //bool addNode(const Node &node);
    //bool addNode(std::string node_name = "");
    //bool removeNode(Node *node);
    //bool removeNode(const std::string &name);
    //bool isolateNode(Node *node);
    //bool isolateNode(const std::string &name);
    //bool setNodeName(Node *node, const std::string &new_name);
    //bool changeNodeName(const std::string &old_name, const std::string &new_name);
    //inline int countEdges() const;
    //Qlist<Node *> nodeList() const;
    //inline int countNodes() const;
    //bool setEdge(Node *u, Node *v);
    //bool setEdge(const std::string &uname, const std::string &vname);
    //bool setEdge(Node *u, Node *v, int w);
    //bool setEdge(const std::string &uname, const std::string &vname, int w);
    //bool removeEdge(Node *u, Node *v);
    //bool removeEdge(const std::string &uname, const std::string &vname);
    //bool hasEdge(Node *u, Node *v) const;
    //bool hasEdge(const std::string &uname, const std::string &vname) const;
    //int weight(Node *u, Node *v) const;
    //int weight(const std::string &uname, const std::string &vname) const;
    //void clearEdges();
    //QString nextNodeName() const;
    //QList edgeSet();
    //QList nodeSet();
    //Node *randomNode();

protected:
//        QSet<Edge> _edgeSet;
//        QSet<Node> _nodeSet;

//private:
//    bool hasDirectedEdge(Node *u, Node *v) const;
        const bool _directed;
        const bool _weighted;

};

#endif // GRAPH_H
