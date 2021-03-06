#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int NMax = 1000;

ifstream fin("input.in");

vector < int > G[NMax];
int jos[NMax];
int desc[NMax];
int viz[NMax];
int tmp = 0;

void FindBridges(int V, int E, int nod, int dad) {
	viz[nod] = 1;
	desc[nod] = ++tmp;
	jos[nod] = desc[nod];

	for (auto it : G[nod]) {
		//daca nodul exista deja in arbore inseamna ca pot sa ma intorc cumva in graf
		if (viz[it] == 1 && it!=dad) {
			jos[nod] = min(jos[nod], desc[it]);
		}

		//daca nu a fost vizitat, fac dfs din el si apoi iau sa vad daca mai pot urca
		else if(viz[it] == 0){
			FindBridges(V, E, it, nod);
			//nodul curent poate sa o ia pe un drum inspre fiii lui si apoi sa urce, marchez acest lucru aici
			jos[nod] = min(jos[it], jos[nod]);

			//daca fiul nu poate sa urce mai sus de nodul curent, e clar ca e muchie punte
			if (jos[it] > desc[nod])
				cout << nod << " " << it << "\n";
		}
	}
}

int main()
{
	int V, E;
	fin >> V >> E;

	for (int i = 1; i <= E; i++) {
		int n1, n2;
		fin >> n1 >> n2;
		G[n1].push_back(n2);
		G[n2].push_back(n1);
	}

	FindBridges(V, E, 1, 0);
	return 0;
}

