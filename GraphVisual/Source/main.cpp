#include "Headers/graphwindow.h"
#include <QApplication>
#include <Headers/algorithm.h>
#include <Headers/graph.h>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GraphWindow w;

    w.show();
    return a.exec();

    return 0;

//    -----------------------------
//    Graph g(false, false);
//    Node *n1 = new Node("1");
//    Node *n2 = new Node("2");
//    Node *n3 = new Node("3");


//    g.addNode(n1);
//    g.addNode(n2);
//    g.addNode(n3);

//    g.addEdge(n1, n2);
//    g.addEdge(n2,n3);
//    g.addEdge(n3, n1);

//    Algorithm a{};
//    QList<Node*> result = a.getEulerianCircuit(g);
//    for(auto node: result) {
//        std::cout << node->name() << " ";
//    }
//    std::cout << std::endl;

//    std::cout << g.edgeSet().size() << std::endl;

//    return 0;

//    -------------------------------------------------

//    Graph g{false, false};

//    g.addNode("1");
//    g.addNode("2");
//    g.addNode("3");

//    g.addEdge(g.getNode("1"), g.getNode("2"));
//    g.addEdge(g.getNode("2"), g.getNode("3"));
//    g.addEdge(g.getNode("3"), g.getNode("1"));

//    Algorithm a{};
//    std::cout << g.getNode("1")->neighbours().size() << std::endl;
//    std::cout << g.getNode("2")->neighbours().size() << std::endl;
//    std::cout << g.getNode("3")->neighbours().size() << std::endl;
//    std::cout << "-----------------------\n";

//    Graph g1 = g;

//    if(a.hasEulerianCircuit(g)) {
//        std::cout << "Graf g ima\n";
//    }
//    else {
//        std::cout << "Graf g nema\n";
//    }

//    if(a.hasEulerianCircuit(g1)) {
//        std::cout << "Grapf g1 ima\n";
//    }
//    else {
//        std::cout << "Graf g1 nema\n";
//    }

//    Graph g1(false, false);
//    Node *n1 = new Node("1");
//    Node *n2 = new Node("2");
//    g1.addNode(n1);
//    g1.addNode(n2);
//    g1.addEdge(n1, n2);

//    Graph g2(g1);
//    Node *n3 = new Node("3");
//    Node *n4 = new Node("4");
//    Node *n5 = new Node("5");
//    Node *n6 = new Node("6");

//    g2.addEdge(g2.getNode("1"), n3);
//    g2.addEdge(g2.getNode("1"), n4);

//    g2.addNode(n3);
//    g2.addNode(n4);
//    g2.addNode(n5);
//    g2.addNode(n6);

//    std::cout << "Graph1 num of neighbours of node 1: " << g1.getNode("1")->neighbours().size() << std::endl;
//    std::cout << "Graph2 num of neighbours of node 1: " << g2.getNode("1")->neighbours().size() << std::endl;
//    std::cout << "Graph1 num of nodes: " << g1.nodeSet().size() << std::endl;
//    std::cout << "Graph2 num of nodes: " << g2.nodeSet().size() << std::endl;

//    return 0;

//    for(auto node : result) {
//        std::cout << node->name() << " ";
//    }
//    std::cout << std::endl << "----------------------------" << std::endl;

    //    for(auto node : result2) {
//        std::cout << node->name() << " ";
//    }
//    std::cout << std::endl;

//    return 0;
}
