#include "catch.hpp"
#include "algorithm.h"
#include "node.h"
#include "graph.h"
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

        REQUIRE(result == expected);
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

        REQUIRE(result == expected);
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

        REQUIRE(result == expected);
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

        REQUIRE(result == expected);
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

        REQUIRE(result == expected);
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

        REQUIRE(result == expected);
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

        REQUIRE(result == expected);
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

        REQUIRE(path == expected);
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
        REQUIRE(path == expected);
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

TEST_CASE("MST", "[mst]")
{
    SECTION("01: Empty graph"){
        Graph* g = new Graph(false, false);

        Algorithm* alg = new Algorithm();
        auto result = alg->MST(*g);

        REQUIRE(result.size()==0);
    }


    SECTION("02: Graph without edges"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->MST(*g);

        REQUIRE(result.size()==1);
    }

    SECTION("03: Random graph"){
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
        g->addEdge(n1, n2, 1);
        g->addEdge(n3, n1, 5);
        g->addEdge(n4, n3, 2);
        g->addEdge(n3, n5, 5);
        g->addEdge(n2, n4, 1);
        g->addEdge(n5, n4, 10);

        Algorithm* alg = new Algorithm();
        auto result = alg->MST(*g);
        int sum = 0;
        for(auto node : g->nodeSet()){
            if(result[node] != nullptr)
                sum += g->weight(node, result[node]);
        }

        REQUIRE(sum==9);
    }
}

TEST_CASE("getBridges", "[bridges]")
{
    SECTION("01: Empty graph"){
        Graph* g = new Graph(false, false);

        Algorithm* alg = new Algorithm();
        auto result = alg->getBridges(*g);

        REQUIRE(result.empty());
    }

    SECTION("02: Graph without edges"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->getBridges(*g);

        REQUIRE(result.empty());
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
        g->addEdge(n1, n3);
        g->addEdge(n3, n4);
        g->addEdge(n3, n5);
        g->addEdge(n4, n5);
        QList<Edge*> expected;
        expected.append(g->getEdge(n1, n2));
        expected.append(g->getEdge(n1, n3));

        Algorithm* alg = new Algorithm();
        auto result = alg->getBridges(*g);

        REQUIRE(result == expected);
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
        g->addEdge(n1, n2);
        g->addEdge(n1, n3);
        g->addEdge(n3, n4);
        g->addEdge(n5, n3);
        g->addEdge(n4, n5);
        QList<Edge*> expected;
        expected.append(g->getEdge(n1, n2));
        expected.append(g->getEdge(n1, n3));

        Algorithm* alg = new Algorithm();
        auto result = alg->getBridges(*g);

        REQUIRE(result == expected);
    }
}


TEST_CASE("getArticulationNodes", "[articulationNodes]")
{
    SECTION("01: Empty graph"){
        Graph* g = new Graph(false, false);

        Algorithm* alg = new Algorithm();
        auto result = alg->getArticulationNodes(*g);

        REQUIRE(result.empty());
    }

    SECTION("02: Graph without edges"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->getArticulationNodes(*g);

        REQUIRE(result.empty());
    }

    SECTION("03: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        Node* n6 = new Node("6");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addNode(n6);
        g->addEdge(n1, n2);
        g->addEdge(n1, n3);
        g->addEdge(n3, n4);
        g->addEdge(n3, n5);
        g->addEdge(n4, n5);
        g->addEdge(n5, n6);
        QSet<Node*> expected;
        expected.insert(n1);
        expected.insert(n3);
        expected.insert(n5);

        Algorithm* alg = new Algorithm();
        auto result = alg->getArticulationNodes(*g);

        REQUIRE(result == expected);
    }

    SECTION("04: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        Node* n5 = new Node("5");
        Node* n6 = new Node("6");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addNode(n5);
        g->addNode(n6);
        g->addEdge(n1, n2);
        g->addEdge(n1, n3);
        g->addEdge(n3, n4);
        g->addEdge(n3, n5);
        g->addEdge(n4, n5);
        g->addEdge(n5, n6);
        QSet<Node*> expected;
        expected.insert(n1);
        expected.insert(n3);
        expected.insert(n4);
        expected.insert(n5);

        Algorithm* alg = new Algorithm();
        auto result = alg->getArticulationNodes(*g);

        REQUIRE(result == expected);
    }

    SECTION("05: Graph without articulation points"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);
        g->addEdge(n3, n4);
        g->addEdge(n4, n1);

        Algorithm* alg = new Algorithm();
        auto result = alg->getArticulationNodes(*g);

        REQUIRE(result.empty());
    }
}

TEST_CASE("isConnected", "[isConnected]")
{
    SECTION("01: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);

        Algorithm* alg = new Algorithm();
        auto result = alg->isConnected(*n1, *n3);

        REQUIRE(result);
    }

    SECTION("02: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addEdge(n1, n2);

        Algorithm* alg = new Algorithm();
        auto result = alg->isConnected(*n1, *n3);

        REQUIRE_FALSE(result);
    }

    SECTION("03: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->isConnected(*n1, *n3);

        REQUIRE(result);
    }

    SECTION("04: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);

        Algorithm* alg = new Algorithm();
        auto result = alg->isConnected(*n1, *n3);

        REQUIRE_FALSE(result);
    }

    SECTION("05: From n to n"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);

        Algorithm* alg = new Algorithm();
        auto result = alg->isConnected(*n1, *n1);

        REQUIRE(result);
    }
}

TEST_CASE("isAllConnected", "[isAllConnected]")
{
    SECTION("01: Empty graph"){
        Graph* g = new Graph(true, false);

        Algorithm* alg = new Algorithm();
        auto result = alg->isAllConnected(*g);

        REQUIRE(result);
    }

    SECTION("02: Graph without edges"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->isAllConnected(*g);

        REQUIRE_FALSE(result);
    }

    SECTION("03: Random directed graph"){
            Graph* g = new Graph(true, false);
            Node* n1 = new Node("1");
            Node* n2 = new Node("2");
            Node* n3 = new Node("3");
            Node* n4 = new Node("4");
            g->addNode(n1);
            g->addNode(n2);
            g->addNode(n3);
            g->addNode(n4);
            g->addEdge(n1, n2);
            g->addEdge(n2, n3);
            g->addEdge(n3, n4);
            g->addEdge(n4, n1);

            Algorithm* alg = new Algorithm();
            auto result = alg->isAllConnected(*g);

            REQUIRE(result);
    }

    SECTION("04: Random directed graph"){
            Graph* g = new Graph(true, false);
            Node* n1 = new Node("1");
            Node* n2 = new Node("2");
            Node* n3 = new Node("3");
            Node* n4 = new Node("4");
            g->addNode(n1);
            g->addNode(n2);
            g->addNode(n3);
            g->addNode(n4);
            g->addEdge(n1, n2);
            g->addEdge(n2, n3);
            g->addEdge(n3, n4);

            Algorithm* alg = new Algorithm();
            auto result = alg->isAllConnected(*g);

            REQUIRE_FALSE(result);
    }

    SECTION("05: Random undirected graph"){
            Graph* g = new Graph(false, false);
            Node* n1 = new Node("1");
            Node* n2 = new Node("2");
            Node* n3 = new Node("3");
            Node* n4 = new Node("4");
            g->addNode(n1);
            g->addNode(n2);
            g->addNode(n3);
            g->addNode(n4);
            g->addEdge(n1, n2);
            g->addEdge(n2, n3);
            g->addEdge(n3, n4);

            Algorithm* alg = new Algorithm();
            auto result = alg->isAllConnected(*g);

            REQUIRE(result);
    }

    SECTION("06: Random undirected graph"){
            Graph* g = new Graph(false, false);
            Node* n1 = new Node("1");
            Node* n2 = new Node("2");
            Node* n3 = new Node("3");
            Node* n4 = new Node("4");
            g->addNode(n1);
            g->addNode(n2);
            g->addNode(n3);
            g->addNode(n4);
            g->addEdge(n1, n2);
            g->addEdge(n3, n4);

            Algorithm* alg = new Algorithm();
            auto result = alg->isAllConnected(*g);

            REQUIRE_FALSE(result);
    }
}

TEST_CASE("Hierholzer", "[hierholzer]")
{
    SECTION("01: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);
        g->addEdge(n3, n4);
        g->addEdge(n4, n1);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);
        expected.append(n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->Hierholzer(*g);

        for(std::string node : result){
            Node *n = g->getNode(node);
            REQUIRE_FALSE(expected.indexOf(n) == -1);
        }
    }

    SECTION("02: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);
        g->addEdge(n3, n4);
        g->addEdge(n1, n4);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);
        expected.append(n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->Hierholzer(*g);

        for(std::string node: result){
            Node *n1 = g->getNode(node);
            REQUIRE_FALSE(expected.indexOf(n1) == -1);
        }
    }

    SECTION("03: Graph without edges"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->Hierholzer(*g);

        REQUIRE(result.empty() == false);
    }
}

TEST_CASE("hasEulerianCircuit", "[hasEulerian]")
{
    SECTION("01: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);
        g->addEdge(n3, n4);
        g->addEdge(n4, n1);

        Algorithm* alg = new Algorithm();
        auto result = alg->hasEulerianCircuit(*g);

        REQUIRE(result);
    }

    SECTION("02: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);
        g->addEdge(n3, n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->hasEulerianCircuit(*g);

        REQUIRE_FALSE(result);
    }

    SECTION("03: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);
        g->addEdge(n3, n4);
        g->addEdge(n1, n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->hasEulerianCircuit(*g);

        REQUIRE(result);
    }

    SECTION("04: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);
        g->addEdge(n1, n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->hasEulerianCircuit(*g);

        REQUIRE_FALSE(result);
    }

    SECTION("05: Graph without edges"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->hasEulerianCircuit(*g);

        REQUIRE_FALSE(result);
    }
}

TEST_CASE("getEulerianCircuit", "[getEulerian]")
{
    SECTION("01: Graph without edges") {
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);

        Algorithm* alg = new Algorithm();
        auto result = alg->getEulerianCircuit(*g);

        REQUIRE(result.empty());
    }

    SECTION("02: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);
        g->addEdge(n3, n4);
        g->addEdge(n4, n1);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);
        expected.append(n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->getEulerianCircuit(*g);

        for(std::string node: result){
            Node *n = g->getNode(node);
            REQUIRE_FALSE(expected.indexOf(n) == -1);
        }
    }

    SECTION("03: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);
        g->addEdge(n3, n4);
        g->addEdge(n1, n4);
        QList<Node*> expected;
        expected.append(n1);
        expected.append(n2);
        expected.append(n3);
        expected.append(n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->getEulerianCircuit(*g);

        for(auto node : result){
            Node *n = g->getNode(node);
            REQUIRE_FALSE(expected.indexOf(n) == -1);
        }
    }

    SECTION("04: Random directed graph"){
        Graph* g = new Graph(true, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n2, n3);
        g->addEdge(n3, n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->getEulerianCircuit(*g);

        REQUIRE(result.empty());
    }

    SECTION("05: Random undirected graph"){
        Graph* g = new Graph(false, false);
        Node* n1 = new Node("1");
        Node* n2 = new Node("2");
        Node* n3 = new Node("3");
        Node* n4 = new Node("4");
        g->addNode(n1);
        g->addNode(n2);
        g->addNode(n3);
        g->addNode(n4);
        g->addEdge(n1, n2);
        g->addEdge(n3, n2);
        g->addEdge(n1, n4);

        Algorithm* alg = new Algorithm();
        auto result = alg->getEulerianCircuit(*g);

        REQUIRE(result.empty());
    }
}
