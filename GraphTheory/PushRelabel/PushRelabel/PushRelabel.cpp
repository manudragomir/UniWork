#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int NMax = 1005;

vector < int > Gr[NMax];
int cost[NMax][NMax];
int exces[NMax];
int height[NMax];

void InitPreFlow(int V, int S) {
	for (int i = 1; i <= V; i++) {
		height[i] = 0;
		exces[i] = 0;
	}

	height[S] = V;

	for (auto vecin : Gr[S]) {
		exces[vecin] = cost[S][vecin];
	}
}

void Inaltare(int nod) {
	int mini = 0x3f3f3f3f;

	for (auto vecin : Gr[nod]) {
		if (cost[nod][vecin] > 0)
			mini = min(mini, height[vecin]);
	}

	height[nod] = 1 + mini;
}

void Pompare(int nodSt, int nodDe) {
	int df = min(exces[nodSt], cost[nodSt][nodDe]);
	cost[nodSt][nodDe] -= df;
	cost[nodDe][nodSt] += df;
	exces[nodSt] = exces[nodSt] - df;
	exces[nodDe] = exces[nodDe] + df;
}

int Preflux(int V, int E, int s, int d) {
	InitPreFlow(V, s);
	int max_flow = 0;
	int nod;
	for (nod = 1; nod <= V; nod++) {
		if (nod != s && nod != d && exces[nod] > 0) {
			//case1 pentru pompare
			int checkSituation = 0;
			for (auto vecin : Gr[nod]) {
				if (height[nod] == 1 + height[vecin] && cost[nod][vecin] > 0) {
					Pompare(nod, vecin);
					nod = 1;
					checkSituation = 1;
					break;
				}
			}

			if (checkSituation == 1)
				continue;

			//case2 pentru inaltare
			bool ok = true;
			for (auto vecin : Gr[nod]) {
				if (height[nod] > height[vecin] && (cost[nod][vecin] > 0)) {
					ok = false;
					break;
				}
			}

			if (ok == true) {
				Inaltare(nod);
				nod = 1;
			}
		}
	}

	return exces[d];
}



int main()
{
	int V, E;
	fin >> V >> E;
	for (int i = 1; i <= E; i++) {
		int n1, n2, fl;
		fin >> n1 >> n2 >> fl;
		Gr[n1].push_back(n2);
		Gr[n2].push_back(n1);
		cost[n1][n2] = fl;
	}

	int flux = Preflux(V, E, 1, V);
	cout << flux << "\n";

	return 0;
}