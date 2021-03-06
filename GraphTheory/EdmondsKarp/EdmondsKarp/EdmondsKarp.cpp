#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

const int NMax = 1005;
vector < int > Grez[NMax];
int cost[NMax][NMax];
vector < pair < int, int > > muchii;

ifstream fin("input.in");

vector <int> BFS(int V, int E, int s, int d)
{
	queue < int > Q;
	int viz[NMax], dad[NMax];

	for (int i = 1; i <= V; i++) {
		viz[i] = 0;
		dad[i] = 0;
	}

	Q.push(s);
	viz[s] = 1;
	dad[s] = -1;
	dad[d] = -1;

	while (!Q.empty()) {
		int nod = Q.front();
		Q.pop();

		if (nod == d)
			break;

		for (auto vecin : Grez[nod]) {
			if (cost[nod][vecin] > 0 && !viz[vecin]) {
				Q.push(vecin);
				dad[vecin] = nod;
				viz[vecin] = 1;
			}
		}
	}

	//restaurare
	while (!Q.empty())
		Q.pop();

	vector < int > v;
	int nod = d;
	while (nod != -1) {
		v.push_back(nod);
		nod = dad[nod];
	}

	reverse(v.begin(), v.end());
	return v;
}

int FordFulkerson(int V, int E, int s, int d)
{
	int max_flow = 0;
	while (true)
	{
		auto drum = BFS(V, E, s, d);
		if (drum.size() == 1) {
			//nu s-a gasit drum
			break;
		}

		else {
			int current_flow = 0x3f3f3f3f;
			for (int i = 0; i < drum.size() - 1; i++) {
				int nod1 = drum[i];
				int nod2 = drum[i + 1];
				current_flow = min(current_flow, cost[nod1][nod2]);
			}

			for (int i = 0; i < drum.size() - 1; i++) {
				int nod1 = drum[i];
				int nod2 = drum[i + 1];
				cost[nod1][nod2] -= current_flow;
				cost[nod2][nod1] += current_flow;
			}

			max_flow += current_flow;
		}
	}

	return max_flow;
}

void EdgeFlux(int V, int E)
{
	for (auto muchie : muchii) {
		if (cost[muchie.second][muchie.first] > 0) {
			cout << muchie.first << " " << muchie.second << " " << cost[muchie.second][muchie.first] << "\n";
		}
	}
}


int main()
{
	int source, dest, V, E;
	fin >> V >> E;
	//fin >> source >> dest;
	source = 1;
	dest = V;

	for (int i = 1; i <= E; i++) {
		int n1, n2, flux;
		fin >> n1 >> n2 >> flux;
		muchii.push_back({ n1, n2 });
		cost[n1][n2] = flux;
		Grez[n1].push_back(n2);
		Grez[n2].push_back(n1);
	}

	int flux = FordFulkerson(V, E, source, dest);
	cout << flux << "\n";
	EdgeFlux(V, E);
	return 0;
}