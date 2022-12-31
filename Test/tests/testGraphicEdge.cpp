#include "catch.hpp"
#include "../GraphVisual/Headers/graphicedge.h"
#include "../GraphVisual/Headers/graphtable.h"
#include <QApplication>


Node *n1;
Node *n2;
GraphicNode *gn1;
GraphicNode *gn2;
GraphicEdge *ge1;

void initialize(){
    n1 = new Node("n1");
    n2 = new Node("n2");
    gn1 = new GraphicNode(n1);
    gn2 = new GraphicNode(n2);
    ge1 = new GraphicEdge(gn1, gn2, 5, false);
}


TEST_CASE("Graphicedge", "[graphicedge]")
{
    SECTION("01: graphicedge"){
        int argc = 0;
        QApplication a{argc, nullptr};
        GraphicEdge *ge = nullptr;
        REQUIRE(ge == nullptr);
    }

    SECTION("02: graphicedge::Constructor"){
        int argc = 0;
        QApplication a{argc, nullptr};
        initialize();
        REQUIRE_FALSE(ge1 == nullptr);
        REQUIRE_FALSE(gn1 == nullptr);
        REQUIRE_FALSE(gn2 == nullptr);
    }

    SECTION("03: graphicedge::getWeight"){
        int argc = 0;
        QApplication a{argc, nullptr};
        initialize();
        int weight = ge1->getWeight();

        REQUIRE(weight == 5);
        REQUIRE_FALSE(ge1 == nullptr);
        REQUIRE_FALSE(gn1 == nullptr);
        REQUIRE_FALSE(gn2 == nullptr);
    }

    SECTION("04: graphicedge::getStart"){
        int argc = 0;
        QApplication a{argc, nullptr};
        initialize();
        GraphicNode *firstNode = ge1->getStart();

        REQUIRE(firstNode == gn1);
        REQUIRE_FALSE(ge1 == nullptr);
        REQUIRE_FALSE(gn1 == nullptr);
        REQUIRE_FALSE(gn2 == nullptr);
    }

    SECTION("05: graphicedge::getEnd"){
        int argc = 0;
        QApplication a{argc, nullptr};
        initialize();
        GraphicNode *secondNode = ge1->getEnd();

        REQUIRE(secondNode == gn2);
        REQUIRE_FALSE(ge1 == nullptr);
        REQUIRE_FALSE(gn1 == nullptr);
        REQUIRE_FALSE(gn2 == nullptr);
    }

    SECTION("06: graphicedge::getCenter"){
        int argc = 0;
        QApplication a{argc, nullptr};
        initialize();
        QPointF centerDistance = QPointF(ge1->getStart()->CenterPosition().rx() - (ge1->getStart()->CenterPosition().rx() - ge1->getEnd()->CenterPosition().rx())/2.0,
                           ge1->getStart()->CenterPosition().ry() - (ge1->getStart()->CenterPosition().ry() - ge1->getEnd()->CenterPosition().ry())/2.0);

        QPointF center = ge1->getCenter();

        REQUIRE(center == centerDistance);
        REQUIRE_FALSE(ge1 == nullptr);
        REQUIRE_FALSE(gn1 == nullptr);
        REQUIRE_FALSE(gn2 == nullptr);
    }

    SECTION("07: graphicedge::setPen"){
        int argc = 0;
        QApplication a{argc, nullptr};
        initialize();
        QPen pen = QPen(Qt::black);
        bool algorithm = true;
        ge1->setPen(pen, algorithm);

        REQUIRE(ge1->pen() == pen);
        REQUIRE_FALSE(ge1 == nullptr);
        REQUIRE_FALSE(gn1 == nullptr);
        REQUIRE_FALSE(gn2 == nullptr);
    }
}

TEST_CASE("GraphTable", "[graphtable]")
{
    SECTION("01: GraphTable::Constructor"){
        int argc = 0;
        QApplication a{argc, nullptr};
        GraphTable *gt = new GraphTable(false, nullptr);

        REQUIRE_FALSE(gt == nullptr);
    }

    SECTION("02: GraphTable::hasGraphicEdge"){
        int argc = 0;
        QApplication a{argc, nullptr};
        GraphTable *gt = new GraphTable(false, nullptr);
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        GraphicNode *gn1 = new GraphicNode(n1);
        GraphicNode *gn2 = new GraphicNode(n2);

        bool edge = gt->hasGraphicEdge(gn1, gn2);

        REQUIRE(edge == false);
    }


    SECTION("03: GraphTable::getNodes/Edges"){
        int argc = 0;
        QApplication a{argc, nullptr};
        GraphTable *gt = new GraphTable(false, nullptr);

        REQUIRE(gt->getNodes().size() == 0);
        REQUIRE(gt->getEdges().size() == 0);
    }

    SECTION("04: GraphTable::getGraphicNode"){
        int argc = 0;
        QApplication a{argc, nullptr};
        GraphTable *gt = new GraphTable(false, nullptr);

        Node *n1 = new Node("n1");
        GraphicNode *node = gt->getGraphicNode(n1);

        REQUIRE(node == nullptr);
    }

    SECTION("05: GraphTable::getGraphicEdge"){
        int argc = 0;
        QApplication a{argc, nullptr};
        GraphTable *gt = new GraphTable(false, nullptr);

        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        Edge *e = new Edge(std::make_pair(n1, n2), 1);
        GraphicEdge *edge = gt->getGraphicEdge(e);

        REQUIRE(edge == nullptr);
    }
}
