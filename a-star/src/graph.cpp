#include "graph.hpp"
#include <queue>
#include <stack>
#include <array>
#include <string>
#include <iostream>

const int INF = std::numeric_limits<int>::max();

std::array<std::string, 20> city2str = {{
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "L",
    "M",
    "N",
    "O",
    "P",
    "R",
    "S",
    "T",
    "U",
    "V",
    "Z"
}};

// Constructor
Graph::Graph(int N) {
    this->N = N;
    this->dist = std::vector<std::vector<int>>(N, std::vector<int>(N, INF));
    this->straight = std::vector<std::vector<int>>(N, std::vector<int>(N, INF));
}

// Add an edge to graph
void Graph::addEdge(int node1, int node2, int d) {
    dist[node1][node2] = d;
    dist[node2][node1] = d;
}

// Add straight distance
void Graph::addStraight(int node1, int node2, int s) {
    straight[node1][node2] = s;
    straight[node2][node1] = s;
}

// structure used in A*
struct Node {
    // node id
    int node;
    // f = g + h
    int g;
    int h;
    int f;
    // parent node
    int p;
};

// compare nodes
struct CmpNode {
    bool operator() (const Node& lhs, const Node& rhs) {
        return lhs.f > rhs.f;
    }
};

// Find shortest path from src to target
void Graph::findShortestPath(int src, int target) {
    std::vector<Node> nodes(N);
    std::vector<bool> open(N, false);
    std::priority_queue<Node, std::vector<Node>, CmpNode> open_que;
    std::vector<bool> closed(N, false);

    for (int i = 0; i < N; i++) {
        nodes[i].node = i;
        nodes[i].g = INF;
        nodes[i].h = INF;
        nodes[i].f = INF;
        nodes[i].p = -1;
    }

    // source node
    nodes[src].g = 0;
    nodes[src].h = straight[src][target];
    nodes[src].f = nodes[src].g + nodes[src].h;
    open[src] = true;
    open_que.push(nodes[src]);

    while (!open_que.empty()) {
        // remove the node whose f(n) is minimum from OPEN and place it on CLOSED
        Node curr = open_que.top();
        open_que.pop();
        open[curr.node] = false;
        closed[curr.node] = true;

        // got you!
        if (curr.node == target) {
            // trace the path
            std::stack<int> path;
            int cost = 0;
            int trace_node = target;
            while (nodes[trace_node].p != -1) {
                path.push(trace_node);
                cost += dist[nodes[trace_node].p][trace_node];
                trace_node = nodes[trace_node].p;
            }
            path.push(trace_node);

            // print path
            std::cout << "Shortest path:" << std::endl; 
            while (!path.empty()) {
                int print_node = path.top();
                path.pop();
                std::cout << city2str[print_node] << std::endl;
            }
            
            // print cost
            std::cout << "\nCost:" << std::endl;
            std::cout << cost << std::endl;

            return;
        }

        // neighbors of current node
        for (int neighbor = 0; neighbor < N; neighbor++) {
            if (neighbor == curr.node || dist[curr.node][neighbor] == INF || closed[neighbor]) {
                continue;
            }
            int n_g = curr.g + dist[curr.node][neighbor];
            int n_h = straight[neighbor][target];
            int n_f = n_g + n_h;
            if (!open[neighbor]) {
                nodes[neighbor].g = n_g;
                nodes[neighbor].h = n_h;
                nodes[neighbor].f = n_f;
                nodes[neighbor].p = curr.node;
                // Place it on OPEN
                open[neighbor] = true;
                open_que.push(nodes[neighbor]);
            }
            else if (n_g < nodes[neighbor].g) {
                // if neighbor is already on OPEN and g(n) or f(n) is lower in the new version,
                // redirect pointers backward from n along path yielding lower g(n) and f(n).
                // ('h' wasn't changed)
                nodes[neighbor].g = n_g;
                nodes[neighbor].f = n_f;
                nodes[neighbor].p = curr.node;
                // Place it on OPEN queue
                open_que.push(nodes[neighbor]);
            }
        }
    }

    std::cout << "no" << std::endl;
}