#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.in");

const int NMax = 500;

vector < pair < int, int > > muchii;

struct muchie
{
	int n1, n2, c;
}g[NMax];

int gr[NMax];

bool cmp(muchie m1, muchie m2)
{
	return m1.c < m2.c;
}

int Find(int nod1)
{
	if (gr[nod1] != nod1)
		return Find(gr[nod1]);

	return gr[nod1];
}

void Join(int nod1, int nod2)
{
	gr[Find(nod2)] = nod1;
}

int main()
{
	int V, E;
	fin >> V >> E;
	for (int i = 1; i <= E; i++)
	{
		fin >> g[i].n1 >> g[i].n2 >> g[i].c;
	}

	sort(g + 1, g + E + 1, cmp);

	for (int i = 1; i <= V; i++)
		gr[i] = i;

	int cost_minim = 0;
	for (int i = 1; i <= E; i++)
	{
		int nod1 = g[i].n1;
		int nod2 = g[i].n2;
		if (Find(nod1) != Find(nod2))
		{
			cost_minim += g[i].c;
			muchii.push_back({ nod1,nod2 });
			Join(Find(nod1), Find(nod2));
		}
	}

	cout << "Cost minim: " << cost_minim << "\n";
	cout << "Numar muchii: " << V - 1 << "\n";
	cout << "Muchiile sunt: \n";
	for (int j = 0; j < muchii.size(); j++)
		cout << muchii[j].first << " " << muchii[j].second << "\n";
}