#ifndef ALGORITHM_H
#define ALGORITHM_H

#include"Headers/Node.h"
#include"Headers/edge.h"
#include"Headers/Graph.h"
#include<iostream>
#include<list>

using namespace std;

class Algorithm{
public:
    list<Node> BFS (Node current);
    void DFS (Node current, map<Node, bool> visited, list<Node> steps);
    bool isConnected (Node u, Node v);
    bool isAllConnected (Graph graph);
    float Dijkstra (Graph graph, Node start, Node end);
    Node minDist(map<Node, float> dist, map<Node, bool> visited);
    void MST (Graph graph);
    list<Edge*> getBridges (Graph graph);
    void bridge (Graph graph, Node node, map<Node, bool> visited,
                  map<Node, int> in, map<Node, int> low_link,
                  map<Node, Node> parent, int time, list<Edge*> result);
    list<Node> getArticulationNodes(Graph graph);
    void articulationNodes (Node node, map<Node, bool> visited,
                            map<Node, int> in, map<Node, int> low_link,
                            map<Node, Node> parent, int time, list<Node> result);
    list<Node> Hierholzer (Graph* graph);
    bool hasEulerianCircuit (Graph graph);
    list<Node> getEulerianCircuit (Graph* graph);
};



#endif // ALGORITHM_H
