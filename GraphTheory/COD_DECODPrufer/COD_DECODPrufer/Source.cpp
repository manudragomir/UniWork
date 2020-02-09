#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("input.in");
const int NMax = 200;
int dg[NMax];//gradul fiecarui nod


vector < int > G[NMax];
int prufer[NMax], fv[NMax];
//int dad[NMax];
priority_queue < pair < int, int > > Q;
vector < pair < int, int > > muchii;

void CodificarePrufer(int V, int E)//O(N^2)
{
	int index = 0;

	//in coada am (frunze,predecesor)
	while (!Q.empty() && index<V-2)
	{
		int nod = -Q.top().first;
		int pred = Q.top().second;
		Q.pop();

		//adaug predecesorul in secv prufer
		//si marchez acest lucru
		prufer[++index] = pred;
		fv[pred]++;


		for (auto vecin : G[nod])
		{
			//sterg fictiv nodul prin reducerea gradelor nodurilor adiacente
			dg[vecin]--;
			if (dg[vecin] == 1)//daca vecinul a devenit frunza il adaug in coada cu predecesorul lui
			{
				//alegerea predecesorului: acel nod vecin care se afla deasupra lui in arbore
				//adica nu a fost sters fictiv - e garantat unul singur
				for (auto vecin2 : G[vecin])
				{
					if (dg[vecin2] != 1)
					{
						Q.push({ -vecin,vecin2 });
						break;
					}	
				}
			}
		}
	}
}

void DecodificarePrufer(int V, int E)//O(N)
{
	priority_queue < int > Qu;

	// pun elementele care nu-s in secv prufer
	for (int i = 1; i <= V; i++)
		if (fv[i] == 0)
			Qu.push({ -i }); 

	int index = 1;
	while (!Q.empty() && index <= V-2)
	{
		int nod2 = -Qu.top();
		Qu.pop();

		int nod1 = prufer[index];
		muchii.push_back({ nod1,nod2 });

		//daca nodul nu mai e in secv prufer
		//pot sa il extrag si pe el ca fiind minim
		fv[nod1]--;
		if (fv[nod1]==0)
			Qu.push(-nod1);
		
		index++;
	}

	int rad = prufer[V - 2];
	muchii.push_back({ rad,-Qu.top() });
	
}

int main()
{
	int V, E;
	fin >> V >> E;
	for (int i = 1; i <= E; i++)
	{
		int nod1, nod2; 
		fin >> nod1 >> nod2;
		G[nod1].push_back(nod2);
		G[nod2].push_back(nod1);
		dg[nod1]++;
		dg[nod2]++;
	}

	for (int i = 1; i <= V; i++)
	{
		if (dg[i] == 1)
		{
			//adaug in coada frunzele si din ce nod provin si le mentin in ordine crescatoare
			Q.push({ -i, G[i].back() });
		}
	}

	CodificarePrufer(V, E);

	for (int i = 1; i <= V - 2; i++)
		cout << prufer[i] << " ";

	cout << "\n";

	DecodificarePrufer(V, E);

	for (auto j = 0; j < muchii.size(); j++)
		cout << muchii[j].first << " " << muchii[j].second << "\n";

	return 0;
}