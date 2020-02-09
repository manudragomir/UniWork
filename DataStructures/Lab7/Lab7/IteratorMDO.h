#pragma once
#include <stack>
#include <vector>
#include "MDO.h"

using namespace std;

class MDO;
struct Node;
typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;

class IteratorMDO {
	friend class MDO;
private:
	//constructorul primeste o referinta catre MDO
	//iteratorul va referi primul element din MDO
	IteratorMDO(const MDO& _c);

	//contine o referinta catre MDOul pe care il itereaza
	const MDO& c;

	/* aici e reprezentarea specifica a iteratorului*/
	int indexCheie;
	int indexValoare;
	vector < Node* > iterate;
	bool invalid{ true };

public:

	//reseteaza pozitia iteratorului la inceputul MDOului
	void prim();

	//muta iteratorul in MDO
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al MDOului)
	bool valid() const;

	//returneaza valoarea elementului din MDO referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;

	void anterior();

	~IteratorMDO() {}

};
