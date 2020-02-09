#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

const int NMax = 150;

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

bool visited[NMax];
int time;
int low[NMax], disc[NMax];

void DFS(int node, int dad) {
	visited[node] = true;
	low[node] = disc[node] = (++time);
	for (auto adjNode : graph[node]) {
		if (adjNode == dad) {
			continue;
		}

		if (visited[adjNode]) {
			low[node] = min(low[node], disc[adjNode]);
		}
	
		else {
			DFS(adjNode, node);
			low[node] = min(low[node], low[adjNode]);
			
			if (dad == -1) {
				if (graph[node].size() > 1) {
					cout << node << " ";
				}
			}
			else if (dad != -1 && low[adjNode] >= disc[node]) {
				cout << node << " ";
			}
		}
	}
}

int main()
{
	int V, E;
	Read(V, E);
	DFS(1, -1);
	return 0;
}