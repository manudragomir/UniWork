#include <vector>
#pragma once
#include "defs.h"
#include "IteratorMD.h"

#include "Lista.h"

using std::vector;

class MD {
	friend class IteratorMD;
private:

	int* urm;
	int capac = 100;
	int primUsed;
	int primLiber;
	int lungime;
	std::pair < TCheie, Lista >* e;
	void spatiuLiber(int, int);
	int aloca();
	void realoca();
	void dealoca(int);
	

public:

	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	//functionalitatea noua
	int adaugaInexistente(MD& md);

	// destructorul MultiDictionarului	
	~MD();



};