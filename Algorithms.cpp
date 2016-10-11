#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>
#include <utility>
// #include <env.h>

// Sorry :(
using namespace std;

// Print vector content
void debugVector(vector<int> vec, string descr);
// Find all the neighbours for node in Graph
vector<int> findNeighbours(int node);
// Finding unused neighbours in path
vector<int> findCandidate(int position, vector<int> path);
// Function for decreasing temperature, returns new temperature
double decreaseTemperature(double initialTemperature, double i);
// Probability of transition, according to Gibbs-Bolcman
double getTransitionProbability(double dE, double T);
// Make transition or not
bool isTransition(double probability);
// In this case "Energy" equal to the  lenght of path
int calculateEnergy(vector<int> path);
// Generating new state
pair< vector<int>, vector< pair<int, int> > > generateStateCandidate(vector<int> path, vector< pair<int, int> >  availableEdges);

// Init Graph
// Really random Graphs and paths implement in Python's notebook, check Alghorithms.ipynb
const vector<vector<int> > Graph = {
	{0, 14}, {0, 6}, {1, 9}, {1, 2}, 
	{1, 13}, {3, 5}, {3, 7}, {4, 10}, 
	{4, 13}, {4, 7}, {5, 11}, {6, 9}, 
	{6, 14}, {7, 13}, {8, 9}, {8, 12}, 
	{9, 12}, {12, 14}
};

const 


int main() {
	// Theoretically, this path is random
	vector<int> currentPathRandom = Graph[2];

	// Print path
	debugVector(currentPathRandom, "Random path:");

	// ===========================
	// ==== GRADIENT DESCENT =====
	// ===========================

	auto currentPath = currentPathRandom;
	while (true) { // Insert nodes to the left
		auto tmpVec = findCandidate(0, currentPath);
		auto newNodeFound = tmpVec[0];
		auto newNode = tmpVec[1];

		if (newNodeFound == 1) {
			currentPath.insert(currentPath.begin(), newNode);
		} else {
			break;
		}
	}

	while (true) { // Insert nodes to the right
		auto tmpVec = findCandidate(currentPath.size() - 1, currentPath);
		auto newNodeFound = tmpVec[0];
		auto newNode = tmpVec[1];

		if (newNodeFound == 1) {
			currentPath.push_back(newNode);
		} else {
			break;
		}
	}

	debugVector(currentPath, "Gradient descent longest simple path: ");

	// ===================================
	// ==== Metropolis with annealing ====
	// ===================================
	currentPath = currentPathRandom;
	auto currentEnergy = calculateEnergy(currentPath);
	double initialTemperature = 100000;
	double endTemperature = 1;
	double T = initialTemperature;

	vector<pair<int, int> > currentPathPairs;
	for (size_t i = 0; i != currentPath.size() - 2; i++) {
		currentPathPairs.push_back(make_pair (currentPath[i], currentPath[i+1]);
	}

	// Make vector of ununsed edges
	vector<pair<int, int> > availableEdges;
	for (auto edge : Graph) {
		bool check_1 = find(currentPathPairs.begin(), currentPathPairs.end(), make_pair (edge[0], edge[1])) == currentPathPairs.end();
		bool check_2 = find(currentPathPairs.begin(), currentPathPairs.end(), make_pair (edge[1], edge[0])) == currentPathPairs.end();
		if (check_1 && check_2) {
			availableEdges.push_back(make_pair (edge[0], edge[1]));
			availableEdges.push_back(make_pair (edge[1], edge[0]));
		}
	}

	for (int step = 0; step != 10000; step++) { // 10000 iterations is enough, believe me
		auto newState = generateStateCandidate(currentPath, availableEdges);
		auto stateCandidate = newState.first;
		auto newAvailableEdges = newState.second;
		auto candidateEnergy = calculateEnergy(stateCandidate);

		if (candidateEnergy >= currentEnergy) {
			currentPath = stateCandidate;
			currentEnergy = candidateEnergy;
			availableEdges = newAvailableEdges;
		} else {
			auto p = getTransitionProbability(currentEnergy - candidateEnergy, T);
			if (isTransition(p)) {
	            currentPath = stateCandidate;
	            currentEnergy = candidateEnergy;
	            availableEdges = newAvailableEdges;
			}
		}
		T = decreaseTemperature(initialTemperature, step);
		if (T <= endTemperature) {
			break;
		}
	}
	debugVector(currentPath, "Metropolis with annealing longest simple path:");

	// ======================================
	// ==== Metropolis without annealing ====
	// ======================================
	// The same as Metropolis with annealing
	// Just comment line #114 - 'T = decreaseTemperature(...)'
	// And set up initialTemperature = 100

	return 0;
}

void debugVector(vector<int> vec, string descr) {
	cout << descr << "\n";
	for (auto e : vec) {
		cout << e << " ";
	}
	cout << "\n";
}

vector<int> findNeighbours(int node) {
	vector<int> neighbours = {};
	for (auto edge : Graph) {
		if (edge[0] == node) {
			neighbours.push_back(edge[1]);
		} else if (edge[1] == node) {
			neighbours.push_back(edge[0]);
		}
	}

	return neighbours;
}

vector<int> findCandidate(int position, vector<int> path) {
	int node = path[position];
	auto nodeNeighbours = findNeighbours(node);

	int candidateFound = false;
	int candidate = 0;

	for (auto node : nodeNeighbours) {
		if (find(path.begin(), path.end(), node) == path.end()) {
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

pair< vector<int>, vector< pair<int, int> > > generateStateCandidate(vector<int> path, vector< pair<int, int> >  availableEdges) {
	if (path.size() <= 1) { // Fuck this node, let's take any available edge as a new path
		auto newPath = availableEdges[rand() % (availableEdges.size() - 1)];
		std::vector<int> path = {newPath.first, newPath.second};

		availableEdges.clear();
		for (auto edge : Graph) {
			availableEdges.push_back(make_pair (edge[0], edge[1]));
			availableEdges.push_back(make_pair (edge[1], edge[0]));
		}
		availableEdges.erase(find(availableEdges.begin(), availableEdges.end(), newPath));
		availableEdges.erase(find(availableEdges.begin(), availableEdges.end(), make_pair (newPath.second, newPath.first)));
	}

	if (rand() % 3 <= 1) { // If 0 or 1 - than add new node
		if (availableEdges.size() == 0) { // All edges are used in path
			return make_pair (path, availableEdges);
		}

		// Get the vector of shuffled nodes like {0, 7, 14, 3, ...}
		vector<int> nodeCandidates(15); // In this case we have nodes 0,1,..,14
		iota(begin(nodeCandidates), end(nodeCandidates), 0);

		if (rand() % 2 == 1) { // Add new edge to the start
			for (auto node : nodeCandidates) {
				bool check_1 = find(availableEdges.begin(), availableEdges.end(), make_pair (node, path[0])) == availableEdges.end();
				bool check_2 = find(availableEdges.begin(), availableEdges.end(), make_pair (path[0], node)) == availableEdges.end();
				bool check_3 = node != path[path.size() - 1];
				bool check_4 = find(path.begin(), path.end(), node) == path.end();

				if (check_1 && check_2 && check_3 && check_4) {
					path.push_back(node); // Add new node to the start
					availableEdges.erase(find(availableEdges.begin(), availableEdges.end(), make_pair (path[0], path[1])));
					availableEdges.erase(find(availableEdges.begin(), availableEdges.end(), make_pair (path[1], path[0])));
					break;
				}
			}
		} else { // Add edge to the end
			for (auto node : nodeCandidates) {
				bool check_1 = find(availableEdges.begin(), availableEdges.end(), make_pair (node, path[path.size() - 1])) == availableEdges.end();
				bool check_2 = find(availableEdges.begin(), availableEdges.end(), make_pair (path[path.size() - 1], node)) == availableEdges.end();
				bool check_3 = node != path[0];
				bool check_4 = find(path.begin(), path.end(), node) == path.end();

				if (check_1 && check_2 && check_3 && check_4) {
					path.push_back(node);
					availableEdges.erase(find(availableEdges.begin(), availableEdges.end(), make_pair (path[path.size() - 1], path[path.size() - 2])));
					availableEdges.erase(find(availableEdges.begin(), availableEdges.end(), make_pair (path[path.size() - 2], path[path.size() - 1])));
					break;
				}
			}
		}
	} else { // Remove edge
		if (rand() % 2 == 1) { // Remove start edge
			availableEdges.push_back(make_pair (path[0], path[1]));
			availableEdges.push_back(make_pair (path[1], path[0]));
			path.erase(path.begin());
		} else { // Remove end edge
			availableEdges.push_back(make_pair (path[path.size() - 1], path[path.size() - 2]));
			availableEdges.push_back(make_pair (path[path.size() - 2], path[path.size() - 1]));
			path.pop_back();
		}
	}

	return make_pair (path, availableEdges);
};
