#include"Headers/algorithm.h"

#include<queue>
#include<QList>
#include<QHash>
#include<QQueue>
#include<QStack>

using namespace std;

QList<Node*> Algorithm::BFS (Node* current){

    QList<Node*> steps;
    QQueue<Node*> q;
    QHash<Node*, bool> visited;

    q.push_back(current);
    visited[current] = true;

    while(!q.empty()){
        current = q.front();
        q.pop_front();
        steps.push_back(current);

        for(auto neighb : current->neighbours())
            if(visited.find(neighb)==visited.end()){
                visited[neighb] = true;
                q.push_back(neighb);
            }
    }

    return steps;
}


void Algorithm::DFS (Node* current, QHash<Node*, bool> &visited, QList<Node*> &steps){

    visited[current] = true;
    steps.push_back(current);

    for(Node* neighb : current->neighbours())
        if(visited.find(neighb)==visited.end())
            DFS(neighb, visited, steps);
}


bool Algorithm::isConnected (Node &u, Node &v){

    QHash<Node*, bool> visited;
    QList<Node*> steps;

    DFS(&u, visited, steps);

    return visited[&v];
}


bool Algorithm::isAllConnected (Graph &graph){

    for (auto node : graph.nodeSet()) {  //ispravio u graph.nodeSet, bilo graph.nodes()

        QHash<Node*, bool> visited;
        QList<Node*> steps;

        DFS(node, visited, steps);

        for(auto v : graph.nodeSet()) //ispravio u graph.nodeSet, bilo graph.nodes()
            if(visited.find(v)==visited.end())
                return false;
    }

    return true;
}


int Algorithm::Dijkstra (Graph &graph, Node* start, Node* end){

    QHash<Node*, bool> visited;
    QHash<Node*, int> dist;
    QHash<Node*, Node*> parent;

    dist[start] = 0;

    Node* current = start;

    while(! (current == end)){
        visited[current] = true;

        for(auto neighb : current->neighbours()){
            if(visited.find(neighb)==visited.end() && (dist.find(neighb)==dist.end() || dist[current] + graph.weight(current, neighb) < dist[neighb])) {// prebacio iz (*current, *neighb) u (current, neighb)
                dist[neighb] = dist[current] + graph.weight(current, neighb); // prebacio iz (*current, *neighb) u (current, neighb)
                parent[neighb] = current;                
            }
        }

        current = minDist(dist, visited);
    }
    return dist[end];
}


Node* Algorithm::minDist(QHash<Node*, int> dist, QHash<Node*, bool> visited){
    int min = numeric_limits<int>::max();
    Node* minNode;
    for (auto iter = dist.constBegin(); iter != dist.constEnd(); ++iter) {
        if(visited.find(iter.key()) == visited.end() && iter.value()<min){
            min = iter.value();
            minNode = iter.key();
        }
    }
    return minNode;
}


//void Algorithm::MST (Graph graph){

//    map<Node, bool> visited;
//    map<Node, Node> parent;
//    map<Node, int> minEdge;

//    priority_queue<std::pair<int, Node*>, vector<std::pair<int, Node*>>, greater<std::pair<int, Node*>>> minDist;

//    int min = numeric_limits<int>::max();
//    Node* begin;
//    Node* end;

//    for(Edge *e : graph.edgeSet()){ //.edges() u .edgeSet()
//        if(e->weight() < min){
//            min = e->weight();
//            begin = e->first();
//            end = e->second();
//        }
//    }

//    minDist.push((0.0, begin));     //TODO *
//    for(auto n : graph.nodes()){
//        if(n != begin)
//            minDist.push((numeric_limits<int>::max(), n));
//    }
//    minEdge[begin] = 0;
//    parent[end] = begin;

//    while(minDist) {
//        node = minDist.top();
//        minDist.pop();

//        Node current = node.second;

//        if(visited[current])
//            continue;

//        visited[current] = true;
//        minEdge[current] = node.first;

//        for(auto neighb : current.neighbours()){
//            if(visited.find(neighb)==visited.end() && minEdge[neighb] > graph.weight(current, neighb)){
//                parent[neighb] = current;
//                minDist.push((graph.weight(*current, *neighb), neighb));
//            }
//        }
//    }

//    //TODO
//    printMST(parent);
//}



QList<Edge*> Algorithm::getBridges (Graph &graph){

    QHash<Node*, bool> visited;
    QHash<Node*, int> in;
    QHash<Node*, int> low_link;
    QHash<Node*, Node*> parent;

    QList<Edge*> result;
    int time = 0;

    for(auto node : graph.nodeSet())  //.nodes() u .nodeSet()
        if(visited.find(node)==visited.end()){
            bridge(graph, node, visited, in, low_link, parent, time, result);
        }

    return result;
}


void Algorithm::bridge (Graph &graph, Node* node, QHash<Node*, bool> &visited,
                    QHash<Node*, int> &in, QHash<Node*, int> &low_link,
                        QHash<Node*, Node*> &parent, int time, QList<Edge*> &result){

    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for(auto neighb : node->neighbours()){
        if(visited.find(neighb)==visited.end()){
            parent[neighb] = node;

            bridge(graph, neighb, visited, in, low_link, parent, time, result);

            low_link[node] = min(low_link[node], low_link[neighb]);

            if(low_link[neighb] > in[node])
                result.push_back(graph.getEdge(node, neighb)); //prebacio iz (*node, *neighb) u (node, neighb)
        }
        else if(!(neighb == parent[node]))
            low_link[node] = min(low_link[node], in[neighb]);
    }


}


// elements repeating in some cases
QList<Node*> Algorithm::getArticulationNodes(Graph &graph){

    QHash<Node*, bool> visited;
    QHash<Node*, int> in;
    QHash<Node*, int> low_link;
    QHash<Node*, Node*> parent;

    QList<Node*> result;
    int time = 0;

    for(auto node : graph.nodeSet()){
        if(visited.find(node)==visited.end()){
            articulationNodes(node, visited, in, low_link, parent, time, result);
        }
    }

    return result;
}

// elements repeating in some cases
void Algorithm::articulationNodes (Node* node, QHash<Node*, bool> &visited,
                                 QHash<Node*, int> &in, QHash<Node*, int> &low_link,
                                   QHash<Node*, Node*> &parent, int time, QList<Node*> &result){

    int children = 0;
    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for(auto neighb : node->neighbours()){
        if(visited.find(neighb)==visited.end()){
            children++;
            parent[neighb] = node;

            articulationNodes(neighb, visited, in, low_link, parent, time, result);

            low_link[node] = min(low_link[node], low_link[neighb]);

            if(!(parent.find(node)==parent.end()) && low_link[neighb] >= in[node])
                result.push_back(node);
        }
        else if(!(neighb == parent[node]))
            low_link[node] = min(low_link[node], in[neighb]);
    }

    if(parent.find(node)==parent.end() && children > 1)
        result.push_back(node);
}


//list<Node*> Algorithm::Hierholzer (Graph* graph){

//    list<Node*> result;

//    stack<Node*> currPath;
//    vector<Node*> cycle;

//    Node* nextNode;

//    Node* currNode = graph->randomNode();
//    std::cout << *currNode << std::endl;
//    currPath.push(currNode);

//    while (!currPath.empty()) {
//        if (currNode->neighbours().size()) {
//            currPath.push(currNode);

//            nextNode = currNode->neighbours().back();

//            graph->removeEdge(currNode, nextNode);
//            currNode->removeNeighbour(nextNode); //need to delete from neighbours list currNode-a nextNode

//            currNode = nextNode;
//        } else {
//            cycle.push_back(currNode);
//            currNode = currPath.top();
//            currPath.pop();
//        }
//    }
//    for (int i = (int) cycle.size() - 1; i >= 1; --i){
//        std::cout << *cycle[i];
//        result.push_back(cycle[i]);
//    }

//    return result;
//}



bool Algorithm::hasEulerianCircuit (Graph &graph){

    if(!isAllConnected(graph)){
        return false;
    }

    for(auto node : graph.nodeSet()){
        if(graph.isDirected() && node->inDeg() != node->outDeg())
            return false;

        if(!graph.isDirected() && node->deg() % 2 != 0)
            return false;
    }

    return true;
}

//TODO Hierholzer before testing
//QList<Node*> Algorithm::getEulerianCircuit (Graph* graph){

//    if(!hasEulerianCircuit(*graph)){
//        //ne postoji ciklus
//        return QList<Node*>();
//    }

//    QList<Node*> result = Hierholzer (graph);

//    return result;
//}


