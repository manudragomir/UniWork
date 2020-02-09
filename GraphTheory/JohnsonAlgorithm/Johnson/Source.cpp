#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

/*
4 5
1 2 -5
2 3 4
1 3 2
1 4 3
3 4 1
*/

using namespace std;

ifstream fin("input.in");

const int NMax = 5000;
const int inf = 0x3f3f3f3f;

vector < pair < int, int > > G[NMax];
vector < pair < int, pair < int, int > > > edges;

void Init(int h[], int V)
{
	for (int i = 1; i <= V; i++)
		h[i] = inf;
}

bool Bellman(int E, int V, int h[])
{
	//o sursa fictiva si adauga muchii de cost 0 catre toate nodurile deja preexistente
	int s = 0;

	for (int i = 1; i <= V; i++)
		edges.push_back({ s,{i,0} });


	Init(h, V);
	h[0] = 0;

	for (int i = 0; i <= V - 1; i++)
	{
		for (int j = 0; j < edges.size(); j++)
		{
			int nod1 = edges[j].first;
			int nod2 = edges[j].second.first;
			int cost = edges[j].second.second;

			if (h[nod2] > h[nod1] + cost)
			{
				h[nod2] = h[nod1] + cost;
			}
		}
	}

	for (int i = 0; i <= V - 1; i++)
	{
		for (int j = 0; j < edges.size(); j++)
		{
			int nod1 = edges[j].first;
			int nod2 = edges[j].second.first;
			int cost = edges[j].second.second;

			if (h[nod2] > h[nod1] + cost)
			{
				return true;
			}
		}
	}

	return false;
}


void Dijkstra(int V, int E, int sursa, int d[])
{
	Init(d, V);
	int viz[NMax];
	for (int i = 1; i <= V; i++)
		viz[i] = 0;

	d[sursa] = 0;
	priority_queue < pair < int, int > > Q;
	Q.push({ 0,sursa });

	while (!Q.empty())
	{
		int nod = Q.top().second;
		int cost = -Q.top().first;
		Q.pop();

		if (viz[nod] == 1)
			continue;

		viz[nod] = 1;
		for (auto vecin : G[nod])
		{
			if (d[vecin.first] > cost + vecin.second)
			{
				d[vecin.first] = cost + vecin.second;
				Q.push({ -d[vecin.first], vecin.first });
			}
		}
	}
}

void Johnson(int E, int V)
{
	int h[NMax];

	if (Bellman(E, V, h) == true)
	{
		cout << "Ciclu negativ!\n";
		return;
	}

	//modificam acum w'(u,v) = w(u,v) + h[u] - h[v]
	//creez un graf pe care sa fac dijkstra-uri din fiecare nod
	for(int i=1; i<=V;i++)
		edges.pop_back();

	for (int j = 0; j < edges.size(); j++)
	{
		int nod1 = edges[j].first;
		int nod2 = edges[j].second.first;
		int cost = edges[j].second.second;
		//cout << nod1 << " " << nod2 << " " << cost + h[nod1] - h[nod2] << "\n";
		G[nod1].push_back({ nod2, cost + h[nod1] - h[nod2] });
	}

	for (int i = 1; i <= V; i++)
	{
		int d[NMax];
		Dijkstra(V, E, i, d);

		for (int j = 1; j <= V; j++)
		{
			if (j != i && d[j]!=inf)
			{
				cout << "Drumul minim de la nodul " << i << " la nodul " << j << " este: " << d[j]+h[j]-h[i] << "\n";
			}
		}
	}
}

int main()
{
	int E, V;
	fin >> V >> E;

	for (int i = 1; i <= E; i++)
	{
		int n1, n2, c;
		fin >> n1 >> n2 >> c;
		edges.push_back({ n1,{n2,c} });
	}

	Johnson(E, V);
	return 0;
}
