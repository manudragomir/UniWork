#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>

using namespace std;

const int NMax = 100;

unordered_map < int, string > culori;

struct Nod {
	vector < int > vecini;
	int color;
	int grade;
};

Nod nodeList[NMax];
vector < int > nodes;

void Read(int& V, int& E) {
	ifstream fin("data.in");

	fin >> V >> E;

	for (int i = 1; i <= V; i++) {
		nodeList[i].color = -1;
		nodeList[i].grade = 0;
	}

	for (int i = 1; i <= E; i++) {
		int n1, n2;
		fin >> n1 >> n2;
		nodeList[n1].vecini.push_back(n2);
		nodeList[n2].vecini.push_back(n1);
		++nodeList[n1].grade;
		++nodeList[n2].grade;
	}

	fin.close();
}

bool checkEdge(int nod, int colr) {
	int check = true;
	for (auto vecin : nodeList[nod].vecini) {
		if (nodeList[vecin].color == colr)
			check = false;
	}

	return check;
}

void nextNode(int& index, int V) {
	++index;
	while (index < V && nodeList[nodes[index]].color != -1)
		++index;
}

void WelshPowell(int V, int E){
	int coloredNodes = 0;
	int index = 0;
	int currentNode = nodes[index];
	int currentColor = 1;

	while (coloredNodes < V){
		nodeList[currentNode].color = currentColor;
		++coloredNodes;
		for (int indexNod = index + 1; indexNod < V; ++indexNod) {
			if (checkEdge(nodes[indexNod], currentColor)) {
				nodeList[nodes[indexNod]].color = currentColor;
				++coloredNodes;
			}
		}

		nextNode(index, V);
		if(index < V)
			currentNode = nodes[index];
		
		++currentColor;
	}
}

void atribuieCulori() {

	culori[1] = "Rosu";
	culori[2] = "Albastru";
	culori[3] = "Galben";
	culori[4] = "Verde";
	culori[5] = "Roz";
	culori[6] = "Violet";
	culori[7] = "Visiniu";
}

int main()
{
	int V, E;
	Read(V, E);
	atribuieCulori();
	
	for (int i = 1; i <= V; i++)
		nodes.push_back(i);

	sort(nodes.begin(), nodes.end(), [&](int n1, int n2) {return nodeList[n1].grade > nodeList[n2].grade; });
	
	WelshPowell(V, E);

	for (int i = 1; i <= V; i++) {
		cout << "Nodul " << i << " se coloreaza " << culori[nodeList[i].color] << "\n";
	}

	return 0;
}