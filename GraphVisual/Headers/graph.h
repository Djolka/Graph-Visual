#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "node.h"

#include <QList>
#include <QSet>
#include <QString>

class Graph {

public:
    explicit Graph(bool directed);
    Graph(Graph &other);

    ~Graph() = default;

	bool isDirected() const;
	bool isUndirected() const;
	void setDirected(bool dir);

	// nodes methods
	Node *getNode(const std::string &name);
	bool hasNode(const std::string &node_name) const;
	bool addNode(Node *node);
    bool removeNode(Node *node);
	bool isolateNode(Node *node);
	inline int countNodes() const { return m_nodes.size(); };
	Node *randomNode();

	// QVariant toVariant() const override;
	// void fromVariant(const QVariant& variant) override;

	// edge methods
	Edge *getEdge(Node *u, Node *v);
	bool addEdge(Node *u, Node *v, int w);
	bool removeEdge(Node *u, Node *v);
	bool hasDirectedEdge(Node *u, Node *v) const;
	bool hasEdge(Node *u, Node *v) const;
	inline int countEdges() const { return m_edges.size(); }
	int weight(Node *u, Node *v) const;

	QList<Edge *> edgeSet();
	QList<Node *> nodeSet();

//    Graph &operator=(const Graph &graph) = default;

protected:
	QList<Edge *> m_edges;
    QList<Node *> m_nodes;

    bool m_directed;
};

#endif // GRAPH_H
