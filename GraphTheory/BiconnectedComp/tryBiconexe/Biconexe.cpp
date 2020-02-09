#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


const int NMax = 100005;
stack < int > st; // for nodes
vector < int > biconectedComponents[NMax]; // pair of nodes
int biComponents;

vector < int > graph[NMax];

void Read(int&V, int& E) {
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
int discovery[NMax], low[NMax];

void DFS(int node, int dad) {
	visited[node] = true;
	discovery[node] = low[node] = (++time);
	for (auto adjNode : graph[node]) {
		if (adjNode == dad) {
			continue;
		}
		else if (visited[adjNode]) {
			low[node] = min(low[node], discovery[adjNode]);
		}
		else {
			st.push(adjNode);
			DFS(adjNode, node);
			low[node] = min(low[node], low[adjNode]);
			if (low[adjNode] >= discovery[node]) {
				while (!st.empty() && st.top() != node) {
					biconectedComponents[biComponents].push_back(st.top());
					st.pop();
				}
				biconectedComponents[biComponents].push_back(node);

				biComponents++;
			}
		}
	}
}

int main() 
{
	int V, E;
	Read(V, E);
	DFS(1, -1);
	cout << biComponents << "\n";
	for (int i = 0; i < biComponents; i++) {
		for (auto node : biconectedComponents[i]) {
			cout << node << " ";
		}
		cout << "\n";
	}
	return 0;
}