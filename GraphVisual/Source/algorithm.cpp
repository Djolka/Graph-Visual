#include"Headers/algorithm.h"

#include<limits>

using namespace std;

list<Node> Algorithm::BFS (Node current){

    list<Node> steps;
    queue<Node> q;
    map<Node, bool> visited;

    q.push(current);
    visited[current] = true;

    while(!q.empty()){
        current = q.front();
        q.pop();
        steps.push_back(current);

        for(auto neighb : current.neighbours())
            if(visited.find(neighb)==visited.end()){
                visited[neighb] = true;
                q.push(neighb);
            }
    }

    return steps;
}

void Algorithm::DFS (Node current, map<Node, bool> visited, list<Node> steps){

    visited[current] = true;
    steps.push_back(current);

    for(auto neighb : current.neighbours())
        DFS(neighb, visited, steps);

}

bool Algorithm::isConnected (Node u, Node v){

    map<Node, bool> visited;
    list<Node> steps;

    DFS(u, visited, steps);

    return visited[v];

}

bool Algorithm::isAllConnected (Graph* graph){

    for (auto node : graph->m_nodes) {

        map<Node, bool> visited;
        list<Node> steps;

        DFS(node, visited, steps);

        for(auto v : graph->m_nodes)
            if(visited.find(v)==visited.end())
                return False;
    }

    return true;
}

float Algorithm::Dijkstra (Graph graph, Node start, Node end){

    map<Node, bool> visited;
    map<Node, float> dist;
    map<Node, Node> parent;

    dist[start] = 0;

    Node current = start;

    while(! (current == end)){
        visited[current] = true;

        for(auto neighb : current.neighbours()){
            if(visited.find(neighb)==visited.end() && (dist.find(neighb)==dist.end() || dist[current] + graph.weight(current, neighb) < dist[neighb])) {
                dist[neighb] = dist[current] + graph->weight(current, neighb);
                parent[neighb] = current;
            }

        }

        current = minDist(dist, visited);     // najmanje udaljen cvor od svih neposecenih
    }

    return dist[end];
}

Node Algorithm::minDist(map<Node, float> dist, map<Node, bool> visited){
    float min = numeric_limits<float>::max();
    Node minNode;
    for(auto i : dist)
        if (visited.find(i.first)==visited.end() && i.second<min){
            min = i.second;
            minNode = i.first;
        }
    return minNode;
}

void Algorithm::MST (Graph graph){

    map<Node, bool> visited;
    map<Node, Node> parent;
    map<Node, int> minEdge;
    priority_queue<pair(float, Node)> minDist;

    for(auto e : graph.edgeSet()){
        if(e.weight() < min){
            min = e.weight();
            begin = e.first();
            end = e.second();
        }
    }

    minDist.push((0.0, begin));
    for(auto n : graph.nodeSet()){
        if(n != begin)
            minDist.push((numeric_limits<float>::max(), n));
    }
    minEdge[begin] = 0;
    parent[end] = begin;

    while(minDist) {
        node = minDist.top();
        minDist.pop();

        current = node.second;

        if(visited[current])
            continue;

        visited[current] = true;
        minEdge[current] = node.first;

        for(auto neighb : current.neighbours()){
            if(visited.find(neighb)==visited.end() && minEdge[neighb] > graph.weight(current, neighb)){
                parent[neighb] = current;
                minDist.push((graph.weight(current, neighb), neighb));
            }
        }
    }

    //TODO
    //printMST(parent);
}


list<Edge> Algorithm::getBridges (Graph* graph){

    map<Node, bool> visited;
    map<Node, int> in;
    map<Node, int> low_link;
    map<Node, Node> parent;

    list<Edge> result;
    int time = 0;

    for(auto node : graph->nodeSet())
        if(visited.find(node)==visited.end())
            bridge(graph, node, visited, in, low_link, parent, time, result);

    return result;
}


void Algorithm::bridge (Graph* graph, Node node, map<Node, bool> visited,
                    map<Node, int> in, map<Node, int> low_link,
                        map<Node, Node> parent, int time, list<Edge> result){

    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for(auto neighb : node->neighbours()){
        if(visited.find(neighb)==visited.end()){
            parent[neighb] = node;

            bridge(graph, neighb, visited, in, low_link, parent, time, result);

            low_link[node] = min(low_link[node], low_link[neighb]);

            if(low_link[neighb] > in[node])
                result.push_back(Edge(n, neighb));
        }
        else if(neighb != parent[node])
            low_link[node] = min(low_link[node], in[neighb]);
    }

}

list<Node> Algorithm::getArticulationNodes(Graph graph){

    map<Node, bool> visited;
    map<Node, int> in;
    map<Node, int> low_link;
    map<Node, Node> parent;

    list<Node> result;
    int time = 0;

    for(auto node : graph.nodes())
        if(visited.find(node)==visited.end())
            articulationNodes(node, visited, in, low_link, parent, time, result);

    return result;
}


void Algorithm::articulationNodes (Node node, map<Node, bool> visited,
                                 map<Node, int> in, map<Node, int> low_link,
                                   map<Node, Node> parent, int time, list<Node> result){

    int children = 0;
    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for(auto neighb : node.neighbours()){
        if(visited.find(neighb)==visited.end()){
            children++;
            parent[neighb] = node;

            articulationNodes(neighb, visited, in, low_link, parent, time, result);

            low_link[node] = min(low_link[node], low_link[neighb]);

            if(!(parent.find(node)==parent.end()) && low_link[neighb] >= in[node])
                result.push_back(node);
        }
        else if(neighb != parent[node])
            low_link[node] = min(low_link[node], in[neighb]);
    }

    if(parent.find(node)==parent.end() && children > 1)
        result.push_back(node);

}


list<Node> Algorithm::Hierholzer (Graph* graph){

    list<Node> result;

    stack<Node> currPath;
    vector<Node> cycle;

    auto currNode = graph->randomNode;
    currPath.push(source);

    while (!currPath.empty()) {

        if (currNode->neighbours().size()) {
            currPath.push(currNode);

            Node nextNode = currNode->neighbours().back();

            graph.removeEdge(currNode, nextNode);

            currNode = nextNode;
        }
        else {
            cycle.push_back(currNode);
            currNode = currPath.top();
            currPath.pop();
        }
    }
    for (int i = (int) cycle.size() - 1; i >= 0; --i)
        result.push_back(cycle[i]);

    return result;

}


bool Algorithm::hasEulerianCircuit (Graph* graph){

    if(!isAllConnected(graph)){
        return False;
    }

    for(auto node : graph->nodeSet())
        if(graph->isDirected() && node->m_inDeg != node->m_outDeg)
            return False;
    if(!graph->isDirected() && node->m_Deg % 2 != 0)
        return False;

    return True;

}


list<Node> Algorithm::getEulerianCircuit (Graph* graph){

    if(!hasEulerianCircuit(graph)){
        //ne postoji ciklus
        return list<Node>();
    }

    list<Node> result = Hierholzer (graph);

    return result;

}




