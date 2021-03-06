#include <iostream>
#include "Dictionar.h"
#include "IteratorDictionar.h"
#include <assert.h>
#include "testExtins.h"
//14. TAD Dicționar – reprezentare sub forma de perechi (cheie, valoare), folosind o TD cu rezolvare
//coliziuni prin liste întrepătrunse

using namespace std;

void testScurt() { //apelam fiecare functie sa vedem daca exista
	Dictionar d;
	assert(d.vid() == true);
	assert(d.dim() == 0); //adaug niste elemente
	assert(d.adauga(5, 5) == NULL_TVALOARE);
	assert(d.adauga(1, 111) == NULL_TVALOARE);
	assert(d.adauga(10, 110) == NULL_TVALOARE);
	assert(d.adauga(7, 7) == NULL_TVALOARE);
	assert(d.adauga(1, 1) == 111);
	assert(d.adauga(10, 10) == 110);
	assert(d.adauga(-3, -3) == NULL_TVALOARE);
	assert(d.dim() == 5);
	assert(d.cauta(10) == 10);
	assert(d.cauta(16) == NULL_TVALOARE);
	assert(d.cauta(7) == 7);
	assert(d.sterge(1) == 1);
	assert(d.sterge(6) == NULL_TVALOARE);
	assert(d.dim() == 4);

	TElem e;
	IteratorDictionar id = d.iterator();
	id.prim();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.element();
		s1 += e.first;
		s2 += e.second;
		id.urmator();
	}


	assert(s1 == 19);
	assert(s2 == 19);
}

int main()
{
	//testScurt();
	//testAllExtins();
	Dictionar d;
	Dictionar m;
	d.adauga(1, 1);
	d.adauga(2, 2);
	d.adauga(3, 3);
	m.adauga(1, 1);
	m.adauga(5, 5);
	m.adauga(3, 10);
	cout << d.actualizeazaValori(m);
	return 0;
}