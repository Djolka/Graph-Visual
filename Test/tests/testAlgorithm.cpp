#include "catch.hpp"
#include "../GraphVisual/Headers/algorithm.h"
#include "../GraphVisual/Headers/node.h"
#include "../GraphVisual/Headers/graph.h"
#include<QList>


TEST_CASE("BFS", "[bfs]")
{
    SECTION("01: Argument is nullptr"){
        Algorithm* alg = new Algorithm();
        auto result = alg->BFS(nullptr);

        REQUIRE(result.size() == 0);
    }

    SECTION("02: Graph with one node"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        g->addNode(n1);
        QList<Node*> expected;
        expected.append(n1);

        Algorithm* alg = new Algorithm();
        auto result = alg->BFS(n1);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }

    SECTION("03: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n1, n2);
        g->addEdge(n3, n1);
        g->addEdge(n4, n3);
        g->addEdge(n3, n5);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);
        expected.append(n4);
        expected.append(n5);

        Algorithm* alg = new Algorithm();
        auto result = alg->BFS(n1);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }

    SECTION("04: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n2, n1);
        g->addEdge(n1, n3);
        g->addEdge(n4, n3);
        g->addEdge(n3, n5);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n3);
        expected.append(n5);

        Algorithm* alg = new Algorithm();
        auto result = alg->BFS(n1);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }

    SECTION("05: Random graph with two components"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n1, n2);
        g->addEdge(n3, n1);
        g->addEdge(n4, n5);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->BFS(n1);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }
}

TEST_CASE("DFS", "[dfs]")
{
    SECTION("01: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n1, n2);
        g->addEdge(n3, n1);
        g->addEdge(n4, n3);
        g->addEdge(n3, n5);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);
        expected.append(n4);
        expected.append(n5);

        Algorithm* alg = new Algorithm();
        QHash<Node*, bool> visited;
        QList<Node*> result;
        alg->DFS(n1, visited, result);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }

    SECTION("02: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n2, n1);
        g->addEdge(n1, n3);
        g->addEdge(n4, n3);
        g->addEdge(n3, n5);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n3);
        expected.append(n5);

        Algorithm* alg = new Algorithm();
        QHash<Node*, bool> visited;
        QList<Node*> result;
        alg->DFS(n1, visited, result);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }

    SECTION("03: Random graph with two components"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n1, n2);
        g->addEdge(n3, n1);
        g->addEdge(n4, n5);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);

        Algorithm* alg = new Algorithm();
        QHash<Node*, bool> visited;
        QList<Node*> result;
        alg->DFS(n1, visited, result);

        for(int i=0; i<result.size(); i++){
            REQUIRE(result[i] == expected[i]);
        }
    }
}

TEST_CASE("Dijkstra", "[dijkstra]")
{
    SECTION("01: Graph with one node"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        g->addNode(n1);

        Algorithm* alg = new Algorithm();
        QList<Node*> path;
        QList<Node*> visit;
        QList<QPair<Node*, Node*>> edges;
        int result = alg->Dijkstra(*g, n1, n1, path, visit, edges);

        REQUIRE(result==0);
    }

    SECTION("02: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n1, n2);
        g->addEdge(n3, n1);
        g->addEdge(n4, n3);
        g->addEdge(n3, n5);
        g->addEdge(n2, n4);
        g->addEdge(n4, n5);
        QList<Node*> expected;
        expected.append(n2);
        expected.append(n4);
        expected.append(n5);

        Algorithm* alg = new Algorithm();
        QList<Node*> path;
        QList<Node*> visit;
        QList<QPair<Node*, Node*>> edges;
        int result = alg->Dijkstra(*g, n2, n5, path, visit, edges);

        REQUIRE(result==2);

        for(int i=0; i<path.size();i++){
            REQUIRE(path[i] == expected[i]);
        }
    }

    SECTION("03: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n2, n1);
        g->addEdge(n1, n3);
        g->addEdge(n4, n3);
        g->addEdge(n3, n5);
        g->addEdge(n5, n2);
        QList<Node*> expected;
        expected.append(n2);
        expected.append(n1);
        expected.append(n3);
        expected.append(n5);

        Algorithm* alg = new Algorithm();
        QList<Node*> path;
        QList<Node*> visit;
        QList<QPair<Node*, Node*>> edges;
        int result = alg->Dijkstra(*g, n2, n5, path, visit, edges);

        REQUIRE(result==3);

        for(int i=0; i<path.size();i++){
            REQUIRE(path[i] == expected[i]);
        }
    }

    SECTION("04: No path from start to end node-undirected"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n1, n2);
        g->addEdge(n3, n1);
        g->addEdge(n4, n5);

        Algorithm* alg = new Algorithm();
        QList<Node*> path;
        QList<Node*> visit;
        QList<QPair<Node*, Node*>> edges;
        int result = alg->Dijkstra(*g, n4, n1, path, visit, edges);

        REQUIRE(result==-1);
    }

    SECTION("05: No path from start to end node-directed"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addEdge(n2, n1);
        g->addEdge(n1, n3);
        g->addEdge(n5, n4);

        Algorithm* alg = new Algorithm();
        QList<Node*> path;
        QList<Node*> visit;
        QList<QPair<Node*, Node*>> edges;
        int result = alg->Dijkstra(*g, n4, n1, path, visit, edges);

        REQUIRE(result==-1);
    }
}


