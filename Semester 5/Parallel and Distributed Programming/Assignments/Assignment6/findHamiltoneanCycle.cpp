#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <future>


class Graph {
private:
    std::vector<int> nodes;
    std::vector<std::vector<int>> edges;

    void generateRandomEdges() {
        edges.resize(nodes.size());
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, nodes.size() - 1);

        int size = static_cast<int>(std::pow(nodes.size(), 2));
        for (int i = 0; i < size / 2; ++i) {
            int node1 = dist(gen);
            int node2 = dist(gen);
            addEdgeIfValid(node1, node2);
        }
    }

    void addEdgeIfValid(int node1, int node2) {
        if (node1 == node2) return;
        if (std::find(edges[node1].begin(), edges[node1].end(), node2) != edges[node1].end()) return;
        edges[node1].push_back(node2);
    }

public:
    Graph(int numNodes) {
        for (int i = 0; i < numNodes; ++i) {
            nodes.push_back(i);
        }
        generateRandomEdges();
    }

    Graph(const std::vector<int>& nodes, const std::vector<std::vector<int>>& edges)
        : nodes(nodes), edges(edges) {}

    const std::vector<int>& getAdjacentNodes(int node) const {
        return edges[node];
    }

    std::vector<int>& getAdjacentNodes(int node) {
        return edges[node];
    }

    const std::vector<int>& getNodes() const {
        return nodes;
    }

    const std::vector<std::vector<int>>& getAllEdges() const {
        return edges;
    }

    int getNumberOfNodes() const {
        return nodes.size();
    }

    void printGraph() const {
        std::cout << "Graph{" << std::endl;
        std::cout << "  Nodes: [";
        for (const auto& node : nodes) {
            std::cout << node << " ";
        }
        std::cout << "]\n  Edges: [\n";
        for (size_t i = 0; i < edges.size(); ++i) {
            std::cout << "    " << i << ": [";
            for (const auto& edge : edges[i]) {
                std::cout << edge << " ";
            }
            std::cout << "]\n";
        }
        std::cout << "  ]\n}" << std::endl;
    }
};



std::mutex mutex;

// Check if a node is already visited
bool isNodeVisited(int node, const std::vector<int>& path) {
    return std::find(path.begin(), path.end(), node) != path.end();
}

// Find a Hamiltonian cycle in the graph
void findHamiltonianCycle(Graph& graph, int currentNode, std::vector<int> path) {
    if (std::find(graph.getAdjacentNodes(currentNode).begin(), graph.getAdjacentNodes(currentNode).end(), 0) != graph.getAdjacentNodes(currentNode).end() 
        && path.size() == graph.getNumberOfNodes()) {
        std::lock_guard<std::mutex> lock(mutex);
        path.push_back(0);
        std::cout << "Found a Hamiltonian cycle: ";
        for (const auto& node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
        return;
    }

    if (path.size() == graph.getNumberOfNodes()) {
        return;
    }

    std::vector<int> neighbors = graph.getAdjacentNodes(currentNode);
    std::vector<std::future<void>> futures;

    for (int neighbor : neighbors) {
        if (!isNodeVisited(neighbor, path)) {
            std::vector<int> newPath = path;
            newPath.push_back(neighbor);

            // Launch async tasks instead of raw threads
            futures.push_back(std::async(std::launch::async, [&graph, neighbor, newPath]() {
                Graph graphCopy = graph; // Create a copy of the graph for thread safety
                findHamiltonianCycle(graphCopy, neighbor, newPath);
            }));

            // Limit the number of concurrent tasks
            if (futures.size() >= 10) {
                for (auto& fut : futures) {
                    fut.get();
                }
                futures.clear();
            }
        }
    }

    for (auto& fut : futures) {
        fut.get();
    }
}

// Start the Hamiltonian cycle search
void startHamiltonianCycleSearch(Graph& graph) {
    std::vector<int> path;
    path.push_back(0);
    findHamiltonianCycle(graph, 0, path);
}

int main() {
    int numNodes;
    std::cout << "Enter the number of nodes in the graph: ";
    std::cin >> numNodes;

    Graph graph(numNodes);
    graph.printGraph();

    auto start = std::chrono::high_resolution_clock::now();

    startHamiltonianCycleSearch(graph);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
