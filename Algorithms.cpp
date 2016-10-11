#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <env.h>
#include <cmath>

// Print vector content
void debugVector(std::vector<int> vec, std::string descr);
// Find all the neighbours for node in Graph
std::vector<int> findNeighbours(int node, const auto &Graph);
// Finding unused neighbours in path
std::vector<int> findCandidate(int position, std::vector<int> path, const auto &Graph);
// Function for decreasing temperature, returns new temperature
double decreaseTemperature(double initialTemperature, double i);
// Probability of transition, according to Gibbs-Bolcman
double getTransitionProbability(double dE, double T);
// Make transition or not
bool isTransition(double probability);
// In this case "Energy" equal to the  lenght of path
int calculateEnergy(auto path);
// Generating new state

	// Init Graph and "random" path
	// Really random Graphs and paths implement in Python's notebook, check Alghorithms.ipynb
const std::vector<std::vector<int> > Graph = {
	{0, 14}, {0, 6}, {1, 9}, {1, 2}, 
	{1, 13}, {3, 5}, {3, 7}, {4, 10}, 
	{4, 13}, {4, 7}, {5, 11}, {6, 9}, 
	{6, 14}, {7, 13}, {8, 9}, {8, 12}, 
	{9, 12}, {12, 14}
};


int main() {
	std::vector<int> currentPathRandom = Graph[2];

	// Print random path
	debugVector(currentPathRandom, "Random path:");

	// ===========================
	// ==== GRADIENT DESCENT =====
	// ===========================

	auto currentPath = currentPathRandom;
	while (true) { // Insert nodes to the left
		auto tmpVec = findCandidate(0, currentPath);
		newNodeFound = tmpVec[0];
		newNode = tmpVec[1];

		if (newNodeFound == 1) {
			currentPath.insert(currentPath.begin(), newNode);
		} else {
			break;
		}
	}
	while (true) { // Insert nodes to the right
		auto tmpVec = findCandidate(currentPath.size() - 1, currentPath);
		newNodeFound = tmpVec[0];
		newNode = tmpVec[1];

		if (newNodeFound == 1) {
			currentPath.push_back(newNode);
		} else {
			break;
		}
	}

	debugVector(currentPath);

	// ===================================
	// ==== Metropolis with annealing ====
	// ===================================

}

void debugVector(std::vector<int> vec, std::string descr) {
	std::cout << descr << "\n";
	for (auto e : vec) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

std::vector<int> findNeighbours(int node, const auto &Graph) {
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

std::vector<int> findCandidate(int position, std::vector<int> path, const auto &Graph) {
	int node = path[position];
	auto nodeNeighbours = findNeighbours(Graph);

	int candidateFound = false;
	int candidate = 0;

	for (auto node : nodeNeighbours) {
		if (std::find(path.begin(), path.end(), node) == path.end()) {
			candidateFound = 1;
			candidate = node;
			break;
		}
	}

	return {candidateFound, candidate};
}

double decreaseTemperature(double initialTemperature, double i) {
	return initialTemperature / i;
}

double getTransitionProbability(double dE, double T) {
	return exp(-dE / T);
}

bool isTransition(double probability) {
	double trigger = ((double) rand() / (RAND_MAX));

	if (trigger < probability) {
		return true;
	} else {
		return false;
	}
}

int calculateEnergy(auto path) {
	return path.size() - 1;
}

std::pair(std::vector<int>, std::vector<std::vector<int> > ) generateStateCandidate(std::vector<int> path, std::vector<std::vector<int> > availableEdges) {
	
};
