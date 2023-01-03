#include "catch.hpp"
#include "node.h"
#include "graph.h"

TEST_CASE("Node", "[node]")
{
    SECTION("01: Node::NodeConstructor (constructing the node withour any parameters given)"){
        Node *n1 = new Node();

        REQUIRE(n1->inDeg() == 0);
        REQUIRE(n1->outDeg() == 0);
        REQUIRE(n1->deg() == 0);
        REQUIRE(n1->name()=="");
        REQUIRE(n1->position()==QPointF(0,0));
    }

    SECTION("02: Node::NodeConstructor1 (constructing the node when the name of the node is given)"){
        Node *n1 = new Node("n1");

        REQUIRE(n1->inDeg() == 0);
        REQUIRE(n1->outDeg() == 0);
        REQUIRE(n1->deg() == 0);
        REQUIRE(n1->name() == "n1");
        REQUIRE(n1->position()==QPointF(0,0));
    }

    SECTION("03: Node::NodeConstructor2 (constructing the node when the name and the position of the said node is given)"){
        Node *n1 = new Node("n1", QPointF(50,50));

        REQUIRE(n1->inDeg() == 0);
        REQUIRE(n1->outDeg() == 0);
        REQUIRE(n1->deg() == 0);
        REQUIRE(n1->name() == "n1");
        REQUIRE(n1->position() == QPointF(50,50));
    }

    SECTION("04: Node::Deg (returning the degree of the node when the edgeset is empty)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        g->addNode(n1);

        REQUIRE(n1->deg() == 0);
    }

    SECTION("05: Node::Deg1 (returning the degree of the node when the edgeset is not empty)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");

        g->addNode(n1);
        g->addNode(n2);

        g->addEdge(n1,n2);

        REQUIRE(n1->deg() == 1);
    }

    SECTION("06: Node::InDeg (returning the number of edges entering the node when there is no edges)"){
        Graph *g = new Graph(true, false);
        Node *n1 = new Node("n1");
        g->addNode(n1);

        REQUIRE(n1->inDeg() == 0);
    }

    SECTION("07: Node::InDeg1 (returning the number of edges entering the node when there are edges)"){
        Graph *g = new Graph(true, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");

        g->addNode(n1);
        g->addNode(n2);

        g->addEdge(n1,n2);

        REQUIRE(n2->inDeg() == 1);
        REQUIRE(n1->inDeg() == 0);
    }

    SECTION("08: Node::OutDeg (returning the number of edges exiting the node when there are none)"){
        Graph *g = new Graph(true, false);
        Node *n1 = new Node("n1");
        g->addNode(n1);

        REQUIRE(n1->outDeg() == 0);
    }

    SECTION("09: Node::OutDeg1 (returning the number of edges exiting the node when there are edges that leave the node)"){
        Graph *g = new Graph(true, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");

        g->addNode(n1);
        g->addNode(n2);

        g->addEdge(n1,n2);

        REQUIRE(n2->outDeg() == 0);
        REQUIRE(n1->outDeg() == 1);
    }

    SECTION("10: Node::Position (returning the position of the node)"){
        Node *n1 = new Node("n1", QPointF(50,50));

        QPointF point = QPointF(50,50);

        REQUIRE(n1->position() == point);
    }

    SECTION("11: Node::Position2 (returning the position of the node when it was not forwarded in constructor)"){
        Node *n1 = new Node("n1");
        REQUIRE(n1->position() == QPointF(0,0));
    }

    SECTION("12: Node::SetPosition (setting the position of the node)"){
        Node *n1 = new Node("n1");

        QPointF point = QPointF(50,50);

        n1->setPosition(QPointF(50,50));

        REQUIRE(n1->position() == point);
    }

    SECTION("13: Node::Name (returning the name of the node)"){
        Node *n1 = new Node("n1");
        std::string name = "n1";

        REQUIRE(n1->name() == name);
    }

    SECTION("14: Node::Compare== (comparing the name of the nodes when the names are differnnt)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");

        REQUIRE_FALSE(n1 == n2);
    }

    SECTION("15: Node::Compare== (comparing the name of the nodes when the nodes are te sahme)"){
        Node *n1 = new Node("n1");
        Node *n2 = n1;

        REQUIRE(n1 == n2);
    }

    SECTION("16: Node::Compare< (check if the first node is alphabetically before the second node)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");

        REQUIRE(n1->name() < n2->name());
    }

    SECTION("17: Node::Compare< (check if the first node is alphabetically before the second node)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n1");

        REQUIRE_FALSE(n1->name() < n2->name());
    }

    SECTION("18: Node::Neighbours (return the list of the neighbours of the node)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        g->addNode(n1);

        QList<Node*> neighbours = QList<Node*>();

        REQUIRE(n1->neighbours() == neighbours);
    }

    SECTION("19: Node::Neighbours (return the list of the neighbours of the node)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        Node *n4 = new Node("n4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1,n2);
        g->addEdge(n1,n3);
        g->addEdge(n1,n4);

        QList<Node*> neighbours = QList<Node*>() << n2 << n3 << n4;

        REQUIRE(n1->neighbours() == neighbours);
    }

    SECTION("20: Node::addNeighbours (if the edge between nodes does not exist, append neighbours list)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addEdge(n1,n2);

        QList<Node*> neighbours = QList<Node*>()<< n2 << n3;

        REQUIRE(n1->addNeighbour(n3)==true);
        REQUIRE(n1->neighbours()==neighbours);
    }

    SECTION("21: Node::addNeighbours (if the node exists, expand its list of neighbours)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addEdge(n1,n2);
        g->addEdge(n1,n3);
        QList<Node*> neighbours = QList<Node*>()<< n2 << n3;

        REQUIRE_FALSE(n1->addNeighbour(n3)==true);
        REQUIRE(n1->neighbours()==neighbours);
    }

    SECTION("22: Node::removeNeighbour (if the nodes are connected, remove the edge between them)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addEdge(n1,n2);
        g->addEdge(n1,n3);

        QList<Node*> neighbours = QList<Node*>()<< n2;

        REQUIRE(n1->removeNeighbour(n3)==true);
        REQUIRE(n1->neighbours()==neighbours);
    }

    SECTION("23: Node::removeNeighbour (if the nodes are connected, remove the edge between them)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addEdge(n1,n2);

        QList<Node*> neighbours = QList<Node*>()<< n2;

        REQUIRE_FALSE(n1->removeNeighbour(n3)==true);
        REQUIRE(n1->neighbours()==neighbours);
    }

    SECTION("24: Node::removeNeighbour (if the nodes are connected, remove the edge between them)"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addEdge(n1,n2);

        QList<Node*> neighbours = QList<Node*>();

        REQUIRE(n1->removeNeighbour(n2)==true);
        REQUIRE(n1->neighbours()==neighbours);
    }
}
