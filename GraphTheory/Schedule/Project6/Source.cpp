#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMax = 15;

int degreeIn[NMax];
int degreeOut[NMax];
void Read(int& V, int&E, int work[], vector < int > G[]) {
	ifstream fin("input.in");
	fin >> V >> E;
	for (int i = 1; i <= V; i++) {
		fin >> work[i];
	}
	for (int i = 0; i < E; i++) {
		int n1, n2;
		fin >> n1 >> n2;
		G[n1].push_back(n2);
		degreeIn[n2]++;
		degreeOut[n1]++;
	}
}

struct {
	int es, ef, ls, lf;
}node[NMax];

bool visited[NMax];
void DFS(int nod, int work[], vector < int > G[], int dad) {
	visited[nod] = true;
	if (dad == -1) {
		node[nod].es = 0;
		node[nod].ef = work[nod];
	}

	int minim = node[nod].es;
	for (auto adjNode : G[nod]) {
		if (!visited[adjNode]) {
			node[adjNode].es = node[nod].ef;
			node[adjNode].ef = node[adjNode].es + work[adjNode];
		}
		else {
			node[adjNode].es = max(node[adjNode].es, node[nod].ef);
			node[adjNode].ef = node[adjNode].es + work[adjNode];
		}
		degreeIn[adjNode]--;
		if (degreeIn[adjNode] == 0) {
			DFS(adjNode, work, G, nod);
			minim = min(minim, node[adjNode].ls);
		}
	}

	node[nod].lf = minim;
	node[nod].ls = minim - work[nod];
}

int main() {
	int V, E, work[NMax];;
	vector < int > G[NMax];
	Read(V, E, work, G);
	for (int i = 1; i <= V; i++) {
		if (degreeIn[i] == 0) {
			DFS(i, work, G, -1);
		}
	}
}