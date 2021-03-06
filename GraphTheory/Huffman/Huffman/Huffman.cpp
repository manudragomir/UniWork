#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>


using namespace std;

ifstream fin("input.in");
int freq[256];//frecventa fiecarui caracter ascii
string cod[256];//aici vom avea codul pentru fiecare caracter


struct Nod {
	char inf;
	int freq;
	string code = "";
	Nod* nextLeft = nullptr;
	Nod* nextRight = nullptr;
};


bool function(Nod* n1, Nod* n2){
	return n1->freq > n2->freq;
}

queue < Nod* > Q;
int viz[300];

//primeste ca parametru un text si returneaza codurile
void CodifHuffman(char str[]){
//creeaza un heap cu frecventele

	//frecventa fiecarui caracter
	for (int i = 0; str[i]; i++) {
		int actual_value = (int)str[i];
		++freq[actual_value];
	}

	vector < Nod* > v;
	for (int i = 0; i < 256; i++) {
		if (freq[i] != 0) {
			//cout << (char)i << " " << freq[i] << "\n";
			Nod* n = new Nod;
			n->freq = freq[i];
			n->inf = (char)i;
			v.push_back(n);
			push_heap(v.begin(), v.end(), function);
		}
	}

	while (v.size()>1) {
		//cout << (v.front())->freq << " " << (v.front())->inf << "\n";
		Nod* cap1 = v.front();
		pop_heap(v.begin(), v.end(), function);
		v.pop_back();

		Nod* cap2 = v.front();
		pop_heap(v.begin(), v.end(), function);
		v.pop_back();

		Nod* rez = new Nod;

		rez->nextLeft = cap1;
		rez->nextRight = cap2;
		rez->freq = cap2->freq + cap1->freq;
		rez->inf = 0;
		
		v.push_back(rez);
		push_heap(v.begin(), v.end(), function);
	}

	Q.push(v.front());
	v.front()->code = "";
	while (!Q.empty()){
		auto nod = Q.front();
		Q.pop();

		//daca e nod intern
		if (nod->inf == 0) {
			//cod pentru fiul stang
			nod->nextLeft->code = nod->code + "0";
			Q.push(nod->nextLeft);

			//cod pentru fiul drept
			nod->nextRight->code = nod->code + "1";
			Q.push(nod->nextRight);
		}

		else{
			cod[(int)nod->inf] = nod->code;
		}
	}
}

int main()
{
	char str[1000];//propozitia citita
	fin.getline(str, 100);

	CodifHuffman(str);
	
	cout << "Codificarea propozitiei este: \n";
	for (int i = 0; str[i]; i++)
		cout << cod[(int)str[i]];

	cout << "\n";

	return 0;
 }