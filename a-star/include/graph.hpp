#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>
#include <stack>

class Graph {
    private:
        // number of nodes
        int N;

        // dist[i][j]: distance from i to j
        std::vector<std::vector<int>> dist;

        // straight[i][j]: straight distance from i to j
        std::vector<std::vector<int>> straight;

    public:
        // Constructor
        Graph(int N);

        // Add an edge to graph
        void addEdge(int node1, int node2, int d);

        // Add straight distance
        void addStraight(int node1, int node2, int s);

        // Find shortest path from src to target
        void findShortestPath(int src, int target);
};

#endif // !_GRAPH_HPP_