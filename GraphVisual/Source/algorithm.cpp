#include"Headers/algorithm.h"

#include<limits>
#include<stack>
#include<queue>

using namespace std;

list<Node*> Algorithm::BFS (Node* current){

    list<Node*> steps;
    queue<Node*> q;
    map<Node*, bool> visited;

    q.push(current);
    visited[current] = true;

    while(!q.empty()){
        current = q.front();
        q.pop();
        steps.push_back(current);

        for(auto neighb : current->neighbours())
            if(visited.find(neighb)==visited.end()){
                visited[neighb] = true;
                q.push(neighb);
            }
    }

    return steps;
}


void Algorithm::DFS (Node* current, map<Node*, bool> &visited, list<Node*> &steps){

    visited[current] = true;
    steps.push_back(current);

    for(Node* neighb : current->neighbours())
        if(visited.find(neighb)==visited.end())
            DFS(neighb, visited, steps);

}

bool Algorithm::isConnected (Node &u, Node &v){

    map<Node*, bool> visited;
    list<Node*> steps;

    DFS(&u, visited, steps);

    return visited[&v];
}

bool Algorithm::isAllConnected (Graph &graph){

    for (auto node : graph.nodes()) {

        map<Node*, bool> visited;
        list<Node*> steps;

        DFS(node, visited, steps);

        for(auto v : graph.nodes())
            if(visited.find(v)==visited.end())
                return false;
    }

    return true;
}

int Algorithm::Dijkstra (Graph &graph, Node* start, Node* end){

    map<Node*, bool> visited;
    map<Node*, int> dist;
    map<Node*, Node*> parent;

    dist[start] = 0;

    Node* current = start;

    while(! (current == end)){
        visited[current] = true;

        for(auto neighb : current->neighbours()){
            if(visited.find(neighb)==visited.end() && (dist.find(neighb)==dist.end() || dist[current] + graph.weight(*current, *neighb) < dist[neighb])) {
                dist[neighb] = dist[current] + graph.weight(*current, *neighb);
                parent[neighb] = current;
            }

        }

        current = minDist(dist, visited);
    }

    return dist[end];
}

Node* Algorithm::minDist(map<Node*, int> dist, map<Node*, bool> visited){
    int min = numeric_limits<int>::max();
    Node* minNode;
    for(auto i : dist)
        if (visited.find(i.first)==visited.end() && i.second<min){
            min = i.second;
            minNode = i.first;
        }
    return minNode;
}

/*
void Algorithm::MST (Graph graph){

    map<Node, bool> visited;
    map<Node, Node> parent;
    map<Node, int> minEdge;

    priority_queue<std::pair<int, Node*>, vector<std::pair<int, Node*>>, greater<std::pair<int, Node*>>> minDist;

    int min = numeric_limits<int>::max();
    Node* begin;
    Node* end;

    for(Edge e : graph.edges()){
        if(e.weight() < min){
            min = e.weight();
            begin = e.getFirst();
            end = e.getSecond();
        }
    }

    minDist.push((0.0, begin));     //TODO *
    for(auto n : graph.nodes()){
        if(n != begin)
            minDist.push((numeric_limits<int>::max(), n));
    }
    minEdge[begin] = 0;
    parent[end] = begin;

    while(minDist) {
        node = minDist.top();
        minDist.pop();

        Node current = node.second;

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
*/

list<Edge*> Algorithm::getBridges (Graph &graph){ //TODO test when graph.getEdge() is done

    map<Node*, bool> visited;
    map<Node*, int> in;
    map<Node*, int> low_link;
    map<Node*, Node*> parent;

    list<Edge*> result;
    int time = 0;

    for(auto node : graph.nodes())
        if(visited.find(node)==visited.end())
            bridge(graph, node, visited, in, low_link, parent, time, result);

    return result;
}


void Algorithm::bridge (Graph &graph, Node* node, map<Node*, bool> &visited,
                    map<Node*, int> &in, map<Node*, int> &low_link,
                        map<Node*, Node*> &parent, int time, list<Edge*> &result){

    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for(auto neighb : node->neighbours()){
        if(visited.find(neighb)==visited.end()){
            parent[neighb] = node;

            bridge(graph, neighb, visited, in, low_link, parent, time, result);

            low_link[node] = min(low_link[node], low_link[neighb]);

            if(low_link[neighb] > in[node])
                result.push_back(graph.getEdge(*node, *neighb));
        }
        else if(!(neighb == parent[node]))
            low_link[node] = min(low_link[node], in[neighb]);
    }

}


list<Node*> Algorithm::getArticulationNodes(Graph &graph){

    map<Node*, bool> visited;
    map<Node*, int> in;
    map<Node*, int> low_link;
    map<Node*, Node*> parent;

    list<Node*> result;
    int time = 0;

    for(auto node : graph.nodes())
        if(visited.find(node)==visited.end())
            articulationNodes(node, visited, in, low_link, parent, time, result);

    return result;
}


void Algorithm::articulationNodes (Node* node, map<Node*, bool> &visited,
                                 map<Node*, int> &in, map<Node*, int> &low_link,
                                   map<Node*, Node*> &parent, int time, list<Node*> &result){

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

/*
list<Node> Algorithm::Hierholzer (Graph* graph){

    list<Node> result;

    stack<Node> currPath;
    vector<Node> cycle;

    auto currNode = graph->randomNode();
    currPath.push(currNode);

    while (!currPath.empty()) {

        if (currNode.neighbours().size()) {
            currPath.push(currNode);

            Node nextNode = currNode.neighbours().back();

            graph->removeEdge(&currNode, &nextNode);

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
*/

bool Algorithm::hasEulerianCircuit (Graph &graph){

    if(!isAllConnected(graph)){
        return false;
    }

    for(auto node : graph.nodes()){
        if(graph.isDirected() && node->in_deg() != node->out_deg())
            return false;

        if(!graph.isDirected() && node->deg() % 2 != 0)
            return false;

    }

    return true;

}

/*
list<Node> Algorithm::getEulerianCircuit (Graph* graph){

    if(!hasEulerianCircuit(*graph)){
        //ne postoji ciklus
        return list<Node>();
    }

    list<Node> result = Hierholzer (graph);

    return result;

}


*/


