#include "algorithm.h"

#include <QHash>
#include <QQueue>
#include <QStack>
#include <algorithm>
#include <limits>
#include <queue>

QList<Node *> Algorithm::BFS(Node *current) {

    QList<Node *> steps;
    if (current == nullptr)
        return steps;

    QQueue<Node *> q;
    QHash<Node *, bool> visited;

    q.push_back(current);
    visited[current] = true;

    while (!q.empty()) {
        current = q.front();
        q.pop_front();
        steps.push_back(current);

        for (auto neighb : current->neighbours())
            if (visited.find(neighb) == visited.end()) {
                visited[neighb] = true;
                q.push_back(neighb);
            }
    }

    return steps;
}

void Algorithm::DFS(Node *current, QHash<Node *, bool> &visited,
                                        QList<Node *> &steps) {

    visited[current] = true;
    steps.push_back(current);

    for (Node *neighb : current->neighbours())
        if (visited.find(neighb) == visited.end())
            DFS(neighb, visited, steps);
}

bool Algorithm::isConnected(Node &u, Node &v) {

    QHash<Node *, bool> visited;
    QList<Node *> steps;

    DFS(&u, visited, steps);

    return visited[&v];
}

bool Algorithm::isAllConnected(Graph &graph) {

    for (auto node : graph.nodeSet()) {

        QHash<Node *, bool> visited;
        QList<Node *> steps;

        DFS(node, visited, steps);

        for (auto v : graph.nodeSet())
            if (visited.find(v) == visited.end())
                return false;
    }

    return true;
}

int Algorithm::Dijkstra(Graph &graph, Node *start, Node *end,
                        QList<Node *> &path, QList<Node *> &visit,
                        QList<QPair<Node *, Node *>> &edges) {

    QHash<Node *, bool> visited;
    QHash<Node *, int> dist;
    QHash<Node *, Node *> parent;

    dist[start] = 0;

    Node *current = start;
    parent[current] = nullptr;

    while (current != nullptr && !(current == end)) {
        visited[current] = true;
        visit.append(current);

        for (auto neighb : current->neighbours()) {
            if (visited.find(neighb) == visited.end() &&
                    (dist.find(neighb) == dist.end() ||
                     dist[current] + graph.weight(current, neighb) < dist[neighb])) {
                dist[neighb] = dist[current] + graph.weight(current, neighb);
                parent[neighb] = current;
                edges.append(qMakePair(current, neighb));
            }
        }

        current = minDist(dist, visited);
    }
    visit.append(end);

    current = end;
    while (current != nullptr) {
        path.append(current);
        current = parent[current];
    }
    std::reverse(path.begin(), path.end());

    if (dist.find(end) == dist.end())
        return -1;

    return dist[end];
}

Node *Algorithm::minDist(QHash<Node *, int> dist, QHash<Node *, bool> visited) {
    int min = std::numeric_limits<int>::max();
    Node *minNode = nullptr;
    for (auto iter = dist.constBegin(); iter != dist.constEnd(); ++iter) {
        if (visited.find(iter.key()) == visited.end() && iter.value() < min) {
            min = iter.value();
            minNode = iter.key();
        }
    }
    return minNode;
}

std::map<Node *, Node *> Algorithm::MST(Graph &graph) {

    std::map<Node *, Node *> parent;
    if (graph.edgeSet().size() == 0) {
        if (graph.nodeSet().size() == 0)
            return parent;
        else {
            parent[graph.randomNode()] = nullptr;
            return parent;
        }
    }

    std::map<Node *, bool> visited;
    std::map<Node *, int> minEdge;

    std::priority_queue<std::pair<int, Node *>,
                        std::vector<std::pair<int, Node *>>,
                        std::greater<std::pair<int, Node *>>> minDist;

    int min = std::numeric_limits<int>::max();
    Node *begin;
    Node *end;

    for (Edge *e : graph.edgeSet()) {
        if (e->weight() < min) {
            min = e->weight();
            begin = e->first();
            end = e->second();
        }
    }

    minDist.push(std::make_pair(0, begin));

    for (Node *n : graph.nodeSet()) {
        if (!(n == begin)) {
            minDist.push(std::make_pair(std::numeric_limits<int>::max(), n));
            minEdge[n] = std::numeric_limits<int>::max();
        }
    }

    minEdge[begin] = 0;
    parent[end] = begin;

    while (!minDist.empty()) {
        auto node = minDist.top();
        minDist.pop();

        Node *current = node.second;

        if (visited.find(current) != visited.end())
            continue;

        visited[current] = true;
        minEdge[current] = node.first;

        for (auto neighb : current->neighbours()) {
            if (visited.find(neighb) == visited.end() &&
                    minEdge[neighb] > graph.weight(current, neighb)) {
                parent[neighb] = current;
                minDist.push(std::make_pair(graph.weight(current, neighb), neighb));
                minEdge[neighb] = graph.weight(current, neighb);
            }
        }
    }

    parent[begin] = nullptr;

    return parent;
}

QList<Edge *> Algorithm::getBridges(Graph &graph) {

    QHash<Node *, bool> visited;
    QHash<Node *, int> in;
    QHash<Node *, int> low_link;
    QHash<Node *, Node *> parent;

    QList<Edge *> result;
    int time = 0;

    for (auto node : graph.nodeSet())
        if (visited.find(node) == visited.end()) {
            bridge(graph, node, visited, in, low_link, parent, time, result);
        }

    return result;
}

void Algorithm::bridge(Graph &graph, Node *node, QHash<Node *, bool> &visited,
                       QHash<Node *, int> &in, QHash<Node *, int> &low_link,
                       QHash<Node *, Node *> &parent, int time,
                    QList<Edge *> &result) {

    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for (auto neighb : node->neighbours()) {
        if (visited.find(neighb) == visited.end()) {
            parent[neighb] = node;

            bridge(graph, neighb, visited, in, low_link, parent, time, result);

            low_link[node] = std::min(low_link[node], low_link[neighb]);

            if (low_link[neighb] > in[node])
                result.push_back(graph.getEdge(node, neighb));
        } else if (!(neighb == parent[node]))
            low_link[node] = std::min(low_link[node], in[neighb]);
    }
}

QSet<Node *> Algorithm::getArticulationNodes(Graph &graph) {

    QHash<Node *, bool> visited;
    QHash<Node *, int> in;
    QHash<Node *, int> low_link;
    QHash<Node *, Node *> parent;

    QSet<Node *> result;
    int time = 0;

    for (auto node : graph.nodeSet()) {
        if (visited.find(node) == visited.end()) {
            articulationNodes(node, visited, in, low_link, parent, time, result);
        }
    }

    return result;
}

void Algorithm::articulationNodes(Node *node, QHash<Node *, bool> &visited,
                                  QHash<Node *, int> &in,
                                  QHash<Node *, int> &low_link,
                                  QHash<Node *, Node *> &parent, int time,
                                  QSet<Node *> &result) {

    int children = 0;
    visited[node] = true;
    in[node] = low_link[node] = ++time;

    for (auto neighb : node->neighbours()) {
        if (visited.find(neighb) == visited.end()) {
            children++;
            parent[neighb] = node;

            articulationNodes(neighb, visited, in, low_link, parent, time, result);

            low_link[node] = std::min(low_link[node], low_link[neighb]);

            if (!(parent.find(node) == parent.end()) && low_link[neighb] >= in[node])
                result.insert(node);
        } else if (!(neighb == parent[node]))
            low_link[node] = std::min(low_link[node], in[neighb]);
    }

    if (parent.find(node) == parent.end() && children > 1)
        result.insert(node);
}

QList<std::string> Algorithm::Hierholzer(Graph *graph) {
    Graph g1(*graph);

    QList<std::string> result;

    QStack<Node *> currPath;
    std::vector<Node *> cycle;

    Node *nextNode;

    Node *currNode = g1.randomNode();
    currPath.push(currNode);

    while (!currPath.empty()) {
        if (!currNode->neighbours().empty()) {
            currPath.push(currNode);

            nextNode = currNode->neighbours().back();

            g1.removeEdge(currNode, nextNode);
//            nextNode->removeNeighbour(currNode); // bez ovog ne radi a trebalo bi jer removeEdge bi trebao da brise susede a ne brise
//            currNode->removeNeighbour(nextNode); // bez ovog ne radi a trebalo bi jer removeEdge bi trebao da brise susede a ne brise

            currNode = nextNode;
        } else {
            cycle.push_back(currNode);
            currNode = currPath.top();
            currPath.pop();
        }
    }
    for (int i = (int)cycle.size() - 1; i >= 0; --i) {
        result.push_back(cycle[i]->name());
    }

    return result;
}

bool Algorithm::hasEulerianCircuit(Graph &graph) {

    if (!isAllConnected(graph)) {
        return false;
    }

    for (auto node : graph.nodeSet()) {
        if (graph.isDirected() && node->inDeg() != node->outDeg())
            return false;

        if (graph.isUndirected() && node->deg() % 2 != 0)
            return false;
    }

    return true;
}

QList<std::string> Algorithm::getEulerianCircuit(Graph *graph) {

    if (!hasEulerianCircuit(*graph)) {
        return QList<std::string>();
    }

    QList<std::string> result = Hierholzer(graph);

    return result;
}
