#include"Headers/algorithm.h"

#include<queue>
#include<QList>
#include<QHash>
#include<QQueue>
#include<QStack>

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

    for (auto node : graph.nodeSet()) {

        QHash<Node*, bool> visited;
        QList<Node*> steps;

        DFS(node, visited, steps);

        for(auto v : graph.nodeSet())
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

    while(!(current == end)){
        visited[current] = true;

        for(auto neighb : current->neighbours()){
            if(visited.find(neighb)==visited.end() && (dist.find(neighb)==dist.end() || dist[current] + graph.weight(current, neighb) < dist[neighb])) {
                dist[neighb] = dist[current] + graph.weight(current, neighb);
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


void Algorithm::MST (Graph graph){

    map<Node*, bool> visited;
    map<Node*, Node*> parent;
    map<Node*, int> minEdge;

    priority_queue<std::pair<int, Node*>, vector<std::pair<int, Node*>>, greater<std::pair<int, Node*>>> minDist;

    int min = numeric_limits<int>::max();
    Node* begin;
    Node* end;

    for(Edge *e : graph.edgeSet()){
        if(e->weight() < min){
            min = e->weight();
            begin = e->first();
            end = e->second();
        }
    }

    minDist.push(make_pair(0, begin));

    for(Node* n : graph.nodeSet()){
        if(!(n == begin)){
            minDist.push(make_pair(numeric_limits<int>::max(), n));
            minEdge[n] = numeric_limits<int>::max();
        }
    }

    minEdge[begin] = 0;
    parent[end] = begin;


    while(!minDist.empty()) {
//        cout<<"while"<<endl;
        auto node = minDist.top();
        minDist.pop();

        Node* current = node.second;

        if(visited.find(current) != visited.end())
            continue;


        visited[current] = true;
        minEdge[current] = node.first;

        for(auto neighb : current->neighbours()){
            if(visited.find(neighb)==visited.end() && minEdge[neighb] > graph.weight(current, neighb)){
                parent[neighb] = current;
                minDist.push(make_pair(graph.weight(current, neighb), neighb));
                minEdge[neighb] = graph.weight(current, neighb);
            }
        }
    }

    //print MST
    for (auto node : graph.nodeSet()){
        if (node != begin){
            cout<< node->name() << " -> " << parent[node]->name() << endl;
        }
    }
}




QList<Edge*> Algorithm::getBridges (Graph &graph){

    QHash<Node*, bool> visited;
    QHash<Node*, int> in;
    QHash<Node*, int> low_link;
    QHash<Node*, Node*> parent;

    QList<Edge*> result;
    int time = 0;

    for(auto node : graph.nodeSet())
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
                result.push_back(graph.getEdge(node, neighb));
        }
        else if(!(neighb == parent[node]))
            low_link[node] = min(low_link[node], in[neighb]);
    }


}

QSet<Node*> Algorithm::getArticulationNodes(Graph &graph){

    QHash<Node*, bool> visited;
    QHash<Node*, int> in;
    QHash<Node*, int> low_link;
    QHash<Node*, Node*> parent;

    QSet<Node*> result;
    int time = 0;

    for(auto node : graph.nodeSet()){
        if(visited.find(node)==visited.end()){
            articulationNodes(node, visited, in, low_link, parent, time, result);
        }
    }

    return result;
}


void Algorithm::articulationNodes (Node* node, QHash<Node*, bool> &visited,
                                 QHash<Node*, int> &in, QHash<Node*, int> &low_link,
                                   QHash<Node*, Node*> &parent, int time, QSet<Node*> &result){

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
                result.insert(node);
        }
        else if(!(neighb == parent[node]))
            low_link[node] = min(low_link[node], in[neighb]);
    }

    if(parent.find(node)==parent.end() && children > 1)
        result.insert(node);
}


QList<Node*> Algorithm::Hierholzer (Graph* graph){

    QList<Node*> result;

    QStack<Node*> currPath;
    vector<Node*> cycle;

    Node* nextNode;

    Node* currNode = graph->randomNode();
    currPath.push(currNode);

    while (!currPath.empty()) {
        if (currNode->neighbours().size()) {
            currPath.push(currNode);

            nextNode = currNode->neighbours().back();

            graph->removeEdge(currNode, nextNode);

            currNode = nextNode;
        } else {
            cycle.push_back(currNode);
            currNode = currPath.top();
            currPath.pop();
        }
    }
    for (int i = (int) cycle.size() - 1; i >= 1; --i){
        result.push_back(cycle[i]);
    }

    return result;
}



bool Algorithm::hasEulerianCircuit (Graph &graph){

    if(!isAllConnected(graph)){
        return false;
    }

    for(auto node : graph.nodeSet()){
        if(graph.isDirected() && node->inDeg() != node->outDeg())
            return false;

        if(graph.isUndirected() && node->deg() % 2 != 0)
            return false;
    }

    return true;
}


QList<Node*> Algorithm::getEulerianCircuit (Graph* graph){

    if(!hasEulerianCircuit(*graph)){
        return QList<Node*>();
    }

    QList<Node*> result = Hierholzer (graph);

    return result;
}


