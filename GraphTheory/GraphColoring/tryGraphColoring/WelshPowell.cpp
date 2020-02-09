//Graph node-coloring using euristic algorithm WelshPowell - O(V^3) time and O(V) memory
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int NMax = 50;
vector < int > graph[NMax];

void Read(int& V, int& E) {
	ifstream fin("input.in");
	fin >> V >> E;
	for (int i = 0; i < E; i++) {
		int n1, n2;
		fin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}
}

int color[NMax], degree[NMax];

bool checkColor(int node1, int actColor) {
	for (auto adjNode : graph[node1]) {
		if (color[adjNode] == actColor)
			return false;
	}

	return true;
}

void WelshPowell(int V, int E) {
	vector < int > nodesList;

	for (int i = 1; i <= V; i++) {
		degree[i] = graph[i].size();
		nodesList.push_back(i);
	}

	sort(nodesList.begin(), nodesList.end(), [](int n1, int n2) {return degree[n1] > degree[n2]; });

	int colors{ 0 };
	for (int i = 0; i < nodesList.size(); i++){
		int currNode = nodesList.at(i);
		if (color[currNode] != 0) {
			continue;
		}
		else {
			color[currNode] = (++colors);
			for (int j = i + 1; j < nodesList.size(); j++) {
				int nextNode = nodesList.at(j);
				if (color[nextNode] == 0 && checkColor(nextNode, colors)) {
					color[nextNode] = colors;
				}
			}
		}
	}	
}

int main() {
	int V, E;
	Read(V, E);
	WelshPowell(V, E);
	for (int i = 1; i <= V; i++) {
		cout << "Node " << i << " has color: " << color[i] << "\n";
	}
	return 0;
}