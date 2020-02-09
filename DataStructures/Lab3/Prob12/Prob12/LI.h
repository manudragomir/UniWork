#pragma once
#include <cstring>
#include "IteratorLI.h"

typedef int TElem;


class LI {
	friend class IteratorLI;
private:
	/* aici e reprezentarea */
	struct node {
		node* prev;
		node* next;
		TElem info;
	};

	int dimen;
	node* prim;
	node* ultim;
	node* creeazaNod(TElem e)
	{
		node* nod = new node;
		nod->info = e;
		nod->next = NULL;
		nod->prev = NULL;
		return nod;
	}
	
public:
	// constructor implicit
	LI();

	// returnare dimensiune
	int dim() const;

	// verifica daca lista e vida
	bool vida() const;

	// returnare element
	//arunca exceptie daca i nu e valid
	TElem element(int i) const;

	// modifica element de pe pozitia i si returneaza vechea valoare
	//arunca exceptie daca i nu e valid
	TElem modifica(int i, TElem e);

	// adaugare element la sfarsit
	void adaugaSfarsit(TElem e);

	// adaugare element pe o pozitie i 
	//arunca exceptie daca i nu e valid
	void adauga(int i, TElem e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElem sterge(int i);

	// cauta element si returneaza prima pozitie pe care apare (sau -1)
	int cauta(TElem e)  const;

	// returnare iterator
	IteratorLI iterator() const;

	int eliminaToate(LI& lista);

	//destructor
	~LI();

};
