#pragma once
#include "IteratorLista.h"

#include <vector>
const int NMax = 100;

typedef int TValue;
using std::vector;

class Lista
{
	friend class IteratorLista;
	friend class IteratorMD;
private:
	int* urm;
	TValue* e;
	int capac = 100;
	int primLiber;
	int primUsed;
public:
	Lista();
	int aloca();
	void realoca();
	void dealoca(int);
	void spatiuLiber(int, int);
	void adauga(TValue);
	bool sterge(TValue,int&);
	vector < TValue > toVector() const;
	IteratorLista iterator() const;
	~Lista();
};

