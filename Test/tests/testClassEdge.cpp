#include "catch.hpp"
#include "edge.h"


TEST_CASE("Edge", "[edge]")
{

    SECTION("01: Edge::First (returning the node the edge is exiting)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        int weight = 5;

        Edge *e = new Edge(std::pair(n1, n2), weight);

        REQUIRE(e->first() == n1);
    }

    SECTION("02: Edge::Second (returning the node the edge is entering)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        int weight = 5;

        Edge *e = new Edge(std::pair(n1, n2), weight);

        REQUIRE(e->second() == n2);
    }

    SECTION("03: Edge::Weight (returning the weight of an edge)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        int weight = 5;

        Edge *e = new Edge(std::pair(n1, n2), weight);

        REQUIRE(e->weight() == weight);
    }

    SECTION("04: Edge::SetWeight (entering value for weight)"){
        Node *n1 = new Node("n1");
        Node *n2 = new Node("n2");
        int weight = 5;
        Edge *e = new Edge(std::pair(n1, n2), weight);
        int newWeight = 10;

        e->setWeight(newWeight);

        REQUIRE(e->weight() == newWeight);
    }
}
