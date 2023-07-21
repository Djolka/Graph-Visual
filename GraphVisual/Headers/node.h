#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QPointF>
#include <iostream>
#include <utility>

class Node {

public:
    Node(const Node *node);
    explicit Node(std::string name);
    ~Node() = default;

    // getters
    unsigned inDeg() const;
    unsigned outDeg() const;
    unsigned deg() const;
    QPointF position() const;
    std::string name() const;

    // overriding operator == so we can compare the nodes by their name
    bool operator==(const Node &second) const;
    bool operator<(const Node &second) const;

    // Node &operator=(const Node &node) = default;
    // friend std::ostream &operator<<(std::ostream &os, const Node &n);
    bool removeNeighbour(Node *v);

    QList<Node *> neighbours();
    bool addNeighbour(Node *n);

private:
	unsigned m_inDeg;
	unsigned m_outDeg;
	unsigned m_deg;
	std::string m_name;
	QPointF m_position;

	QList<Node *> m_neighbours;

	void incInDeg();
	void incOutDeg();
	void decInDeg();
	void decOutDeg();
	void incDeg();
	void decDeg();

	friend class Graph;
};

#endif // NODE_H
