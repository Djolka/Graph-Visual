#ifndef ALGORITHM_H
#define ALGORITHM_H

#include"Headers/node.h"
#include"Headers/edge.h"
#include"Headers/graph.h"
#include<iostream>

#include<QList>
#include<QPair>

class Algorithm{
public:
    Algorithm(){}

    QList<Node*> BFS (Node* current);
    void DFS (Node* current, QHash<Node*, bool> &visited, QList<Node*> &steps);
    bool isConnected (Node &u, Node &v);
    bool isAllConnected (Graph &graph);
    int Dijkstra (Graph &graph, Node* start, Node* end,  QList<Node*> &path, QList<Node*> &visit,  QList<QPair<Node*, Node*>> &edges);
    Node* minDist(QHash<Node*, int> dist, QHash<Node*, bool> visited);
    std::map<Node*, Node*> MST (Graph &graph);
    QList<Edge*> getBridges (Graph &graph);
    void bridge (Graph &graph, Node* node, QHash<Node*, bool> &visited,
                  QHash<Node*, int> &in, QHash<Node*, int> &low_link,
                  QHash<Node*, Node*> &parent, int time, QList<Edge*> &result);
    QSet<Node*> getArticulationNodes(Graph &graph);
    void articulationNodes (Node* node, QHash<Node*, bool> &visited,
                            QHash<Node*, int> &in, QHash<Node*, int> &low_link,
                            QHash<Node*, Node*> &parent, int time, QSet<Node*> &result);
    QList<std::string> Hierholzer (Graph graph);
    bool hasEulerianCircuit (Graph &graph);
    QList<std::string> getEulerianCircuit (Graph graph);
};



#endif // ALGORITHM_H
