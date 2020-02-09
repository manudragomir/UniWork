#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("input.in");
const int NMax = 500;
const int inf = 0x3f3f3f3f;
vector < pair < int, int > > G[NMax];
int dist[NMax];
int parent[NMax];
int viz[NMax];

void Prim(int V, int E)
{
	for (int i = 1; i <= V; i++)
		dist[i] = inf, viz[i] = 0;
	priority_queue < pair < int, int > > Q;
	Q.push({ 0,1 });
	dist[1] = 0;
	while (!Q.empty())
	{
		int nod = Q.top().second;
		Q.pop();

		if (viz[nod])
			continue;

		viz[nod] = 1;

		for (auto vecin : G[nod])
		{
			if(viz[vecin.first] == 0 && dist[vecin.first] > vecin.second)
			{
				dist[vecin.first] = vecin.second;
				Q.push({ -dist[vecin.first], vecin.first });
				parent[vecin.first] = nod;
			}
		}
	}
	
	int cost_minim = 0;
	for (int i = 2; i <= V; i++)
		cost_minim += dist[i];

	cout << "Cost minim: " << cost_minim << "\n";
	cout << "Muchiile sunt: \n";
	for (int i = 2; i <= V; i++)
	{
		cout << i << " " << parent[i] << "\n";
	}
}

int main()
{
	int V, E;
	fin >> V >> E;
	for (int i = 1; i <= E; i++)
	{
		int n1, n2, c;
		fin >> n1 >> n2 >> c;
		G[n1].push_back({ n2,c });
		G[n2].push_back({ n1,c });
	}

	Prim(V, E);
	return 0;
}