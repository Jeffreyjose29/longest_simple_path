#include <iostream>
#include <vector>
#include <string>

// Print vector content
void debugVector(std::vector<int> vec, std::string descr) {
	std::cout << descr << "\n";
	for (auto e : vec) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

// Find all the neighbours for node in Graph
std::vector<int> findNeighbours(int node, auto Graph) {
	std::vector<int> neighbours = {};
	for (auto edge : Graph) {
		if (edge[0] == node) {
			neighbours.push_back(edge[1]);
		} else if (edge[1] == node) {
			neighbours.push_back(edge[0]);
		}
	}

	return neighbours;
}

// Finding unused neighbours in path
// For "Gradient descent" algo
std::vector<int> findCandidate(int position, std::vector<int> path, auto Graph) {
	int node = path[position];
	auto nodeNeighbours = findNeighbours(Graph);
}

int main() {
	// Init Graph and "random" path
	// Really random Graphs and paths implement in Python's realization, check Alghorithms.ipynb
	std::vector<std::vector<int> > Graph = {{0, 14}, {0, 6}, {1, 9}, {1, 2}, 
											{1, 13}, {3, 5}, {3, 7}, {4, 10}, 
											{4, 13}, {4, 7}, {5, 11}, {6, 9}, 
											{6, 14}, {7, 13}, {8, 9}, {8, 12}, 
											{9, 12}, {12, 14}};
	std::vector<int> currentPathRandom = Graph[2];

	// Print random path
	debugVector(currentPathRandom, "Random path:");

	// auto c = findNeighbours(0, Graph);
	// debugVector(c, "Neighbours for '0' node:");
}