#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <utility>
#include <QPointF>
#include <QList>

class Node{

public:
    Node();
    explicit Node(std::string);
    explicit Node(std::string, QPointF position);

    //getters
    unsigned in_deg() const;
    unsigned out_deg() const;
    unsigned deg() const;
    QPointF position() const;
    std::string name() const;

    //setters
    void set_position(const QPointF &position);

    //overriding operator == so we can compare the nodes by their name
    bool operator==(const Node &second) const;

    bool operator<(const Node &second) const;

    QList<Node> neighbours();


private:

    unsigned m_in_deg;
    unsigned m_out_deg;
    unsigned m_deg;
    std::string m_name;
    QPointF m_position;

    QList<Node> m_neighbours;

    void inc_in_deg();
    void inc_out_deg();
    void dec_in_deg();
    void dec_out_deg();
    void inc_deg();
    void dec_deg();
    void set_name(std::string name);

    friend class Graph;
};


#endif // NODE_H
