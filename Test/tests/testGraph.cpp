#include "catch.hpp"
#include "graph.h"


TEST_CASE("Graph", "[graph]")
{

    SECTION("01: Graph::addNode"){
        Graph *g = new Graph(false, false);

        REQUIRE(g->nodeSet().size() == 0);
        REQUIRE(g->edgeSet().size() == 0);
    }

    SECTION("02: Graph::addNode1"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node();

        QList<Node *> nodes_list = QList<Node *>() << n1;

        g->addNode(n1);

        REQUIRE(g->nodeSet() == nodes_list);
        REQUIRE(n1->deg() == 0);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(g->nodeSet().size() == nodes_list.size());
    }

    SECTION("03: Graph::addNode2"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node();
        Node *n2 = new Node();

        QList<Node *> nodes_list = QList<Node *>() << n1 << n2;

        g->addNode(n1);
        g->addNode(n2);

        REQUIRE(g->nodeSet() == nodes_list);
        REQUIRE(n1->deg() == 0);
        REQUIRE(n2->deg() == 0);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(g->nodeSet().size() == nodes_list.size());
    }

    SECTION("04: Graph::deleteNode"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);
        QList<Node *> nodes_list = QList<Node *>() << n1;

        g->removeNode(n2);

        REQUIRE(g->nodeSet() == nodes_list);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(g->nodeSet().size() == nodes_list.size());
    }

    SECTION("05: Graph::deleteNodeByName"){
        Graph *g = new Graph(false, false);
        Node *n1 = new Node("1");
        Node *n2 = new Node("2");
        g->addNode(n1);
        g->addNode(n2);

        QList<Node *> nodes_list = QList<Node *>() << n2;

        g->removeNode("1");

        REQUIRE(g->nodeSet() == nodes_list);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(g->nodeSet().size() == nodes_list.size());
    }

    SECTION("06: Graph::isWeightedfalse"){
        Graph *g = new Graph(false, false);

        REQUIRE(g->isWeighted() == false);
        REQUIRE(g->isUnweighted() == true);
    }

    SECTION("07: Graph::isWeightedtrue"){
        Graph *g = new Graph(false, true);

        REQUIRE(g->isWeighted() == true);
        REQUIRE(g->isUnweighted() == false);

    }

    SECTION("08: Graph::isDirectedfalse"){
        Graph *g = new Graph(false, false);

        REQUIRE(g->isDirected() == false);
        REQUIRE(g->isUndirected() == true);
    }

    SECTION("09: Graph::isDirectedtrue"){
        Graph *g = new Graph(true, false);

        REQUIRE(g->isDirected() == true);
        REQUIRE(g->isUndirected() == false);
    }

    SECTION("10: Graph::setDirected"){
        Graph *g = new Graph(false, false);

        g->setDirected(true);
        REQUIRE(g->isDirected() == true);
        g->setDirected(false);
        REQUIRE(g->isDirected() == false);
    }

    SECTION("11: Graph::getNode"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        g->addNode(n1);
        Node *get = g->getNode("n1");

        REQUIRE(n1 == get);
    }

    SECTION("12: Graph::hasNode"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        g->addNode(n1);
        bool hasNode = g->hasNode("n1");

        REQUIRE(hasNode == true);
        REQUIRE(g->nodeSet().size() == 1);
    }

    SECTION("13: Graph::getEdge"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        Edge* edge = g->getEdge(n1, n2);

        REQUIRE(edge == nullptr);
        REQUIRE(g->edgeSet().size() == 0);
    }


    SECTION("14: Graph::addEdgeUndirected"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        bool add = g->addEdge(n1,n2);
        bool add1 = g->addEdge(n2,n1);

        Edge* edge = g->getEdge(n1, n2);

        REQUIRE(add == true);
        REQUIRE(add1 == false);
        REQUIRE_FALSE(edge == nullptr);
        REQUIRE(g->edgeSet().size() == 1);
        REQUIRE(g->nodeSet().size() == 3);
    }


    SECTION("15: Graph::addEdgeDirected"){
        Graph *g = new Graph(true, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Node *n3 = new Node("n3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        bool add = g->addEdge(n1,n2);
        bool add1 = g->addEdge(n2,n1);

        Edge* edge = g->getEdge(n1, n2);
        Edge* edge1 = g->getEdge(n2, n1);

        REQUIRE(add == true);
        REQUIRE(add1 == true);
        REQUIRE_FALSE(edge == nullptr);
        REQUIRE_FALSE(edge1 == nullptr);
        REQUIRE(g->edgeSet().size() == 2);
        REQUIRE(g->nodeSet().size() == 3);
    }


    SECTION("16: Graph::isolateNode"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);
        g->addEdge(n1,n2);

        bool isolate = g->isolateNode(n1);

        REQUIRE(isolate == true);
        REQUIRE(g->nodeSet().size() == 2);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(n1->deg() == 0);
        REQUIRE(n2->deg() == 0);
    }

    SECTION("17: Graph::countNodes"){
        Graph *g = new Graph(false, false);

        int numNodes= g->countNodes();

        REQUIRE(numNodes == 0);
    }

    SECTION("18: Graph::countNodes1"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        g->addNode(n1);

        int numNodes= g->countNodes();

        REQUIRE(numNodes == g->nodeSet().size());
    }

    SECTION("19: Graph::removeEdgeUndirected"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);
        g->addEdge(n1,n2);

        bool remove = g->removeEdge(n1,n2);

        REQUIRE(remove == true);
        REQUIRE(n1->deg() == 0);
        REQUIRE(n2->deg() == 0);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(g->nodeSet().size() == 2);
    }

    SECTION("20: Graph::removeEdgeDirected"){
        Graph *g = new Graph(true, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);
        g->addEdge(n1,n2);

        bool remove = g->removeEdge(n1,n2);

        REQUIRE(remove == true);
        REQUIRE(n1->outDeg() == 0);
        REQUIRE(n2->inDeg() == 0);
        REQUIRE(g->edgeSet().size() == 0);
        REQUIRE(g->nodeSet().size() == 2);
    }

    SECTION("21: Graph::hasDirectedEdge"){
        Graph *g = new Graph(true, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);
        g->addEdge(n1,n2);

        bool hasDirEdge = g->hasDirectedEdge(n1,n2);
        bool hasDirEdge1 = g->hasDirectedEdge(n2,n1);

        REQUIRE(hasDirEdge == true);
        REQUIRE(hasDirEdge1 == false);
        REQUIRE(n1->outDeg() == 1);
        REQUIRE(n2->inDeg() == 1);
        REQUIRE(g->edgeSet().size() == 1);
        REQUIRE(g->nodeSet().size() == 2);
    }

    SECTION("22: Graph::hasEdgeUndirected"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);

        g->addEdge(n1,n2);

        bool hasEdge = g->hasEdge(n1,n2);

        REQUIRE(hasEdge == true);
    }

    SECTION("23: Graph::hasEdgeDirected"){
        Graph *g = new Graph(true, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);

        g->addEdge(n1,n2);

        bool hasEdge = g->hasEdge(n1,n2);
        bool hasEdge1 = g->hasEdge(n2,n1);

        REQUIRE(hasEdge == true);
        REQUIRE(hasEdge1 == false);
    }

    SECTION("24: Graph::countEdges"){
        Graph *g = new Graph(false, false);

        REQUIRE(g->countEdges() == 0);
    }

    SECTION("25: Graph::countEdges"){
        Graph *g = new Graph(false, false);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        g->addNode(n1);
        g->addNode(n2);

        g->addEdge(n1,n2);

        REQUIRE(g->countEdges() == 1);
    }
}
