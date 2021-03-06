#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

const int NMax = 250;
ifstream fin("input.in");
int grad[NMax];
vector < int > G[NMax];
stack < int > st;
stack < int > rez;

struct muchie {
	int n1, n2;
	bool sters = false;
}v[NMax];

void DetectCycle(int V, int E){
	st.push(1);

	while (!st.empty()) {
		int nod = st.top();

		if (G[nod].size() == 0) {
			//am explorat tot; adaug la stiva rezultat si scot din actuala stiva
			rez.push(nod);
			st.pop();
		}

		else {
			//mai am muchi de parcurs si o sterg pe ultima
			int next = G[nod].back();
			G[nod].pop_back();
			
			//daca am sters-o din cealalta extremitate anterior, nu mai parcurg nimic
			if (v[next].sters == true)
				continue;

			//daca nu, merg pe cealalta extremitate
			if (v[next].n1 == nod)
				st.push(v[next].n2);

			else
				st.push(v[next].n1);

			v[next].sters = true;

		}
	}
}

int main()
{
	int V, E;
	fin >> V >> E;
	for (int i = 1; i <= E; i++){
		//creez muchia
		fin >> v[i].n1 >> v[i].n2;

		//asignez muchia nodului n1 si nodului n2
		G[v[i].n1].push_back(i);
		G[v[i].n2].push_back(i);

		++grad[v[i].n1];
		++grad[v[i].n2];
	}

	for (int i = 1; i <= V; i++) {
		if (grad[i] % 2 != 0) {
			cout << "Nu se poate forma ciclu eulerian\n";
			return 0;
		}
	}

	DetectCycle(V, E);

	while (!rez.empty()) {
		cout << rez.top() << " ";
		rez.pop();
	}
	return 0;
}