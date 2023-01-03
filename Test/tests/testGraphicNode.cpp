#include "catch.hpp"
#include "graphicnode.h"
#include "node.h"

TEST_CASE("Graphic Node Class", "[graphicNode]")
{
    SECTION("getNode"){
        Node* expected = new Node();
        GraphicNode* gNode = new GraphicNode(expected);

        Node* result = gNode->getNode();

        REQUIRE(result == expected);
    }

    SECTION("getNode nullptr"){
        GraphicNode* gNode = new GraphicNode(nullptr);

        Node* result = gNode->getNode();

        REQUIRE(result == nullptr);
    }

    SECTION("setBrush"){
        GraphicNode* gNode = new GraphicNode(new Node());
        QBrush expected = QBrush(Qt::red);

        gNode->setBrush(expected, false);

        REQUIRE(gNode->getBrush()==expected);
    }

    SECTION("getBrush default value"){
        GraphicNode* gNode = new GraphicNode(new Node());
        QBrush expected = QBrush(Qt::white);

        auto result = gNode->getBrush();

        REQUIRE(result == expected);
    }

    SECTION("type override"){
        GraphicNode* gNode = new GraphicNode(new Node());
        int expected = 1;

        auto result = gNode->type();

        REQUIRE(result==expected);
    }
}
