#pragma once
#include <algorithm>

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

const int NULL_TVALOARE = -0x3f3f3f3f;
const int NULL_TCHEIE = -0x3f3f3f3f;
const int Hesh = 60000;

class IteratorDictionar;

class Dictionar {
	friend class IteratorDictionar;
private:
	/* aici e reprezentarea */
	int dimen;
	int v[15] = { 97, 769, 6151, 98317, 196613, 393241 };
	int index;
	void Rehashing();

	int primLiber;
	int m;
	TElem* ch; //vector de TElemente: perechi cu prima valoare cheia, si a doua valoarea
	int* urm; //vector de urm

	int d(TCheie nr) const{
		return HashCode(nr) % this->m;
	}

	int HashCode(TCheie c) const {
		return (int)c + Hesh;
	}

	TCheie DeHash(int hash) const {
		return (TCheie)hash - Hesh;
	}

	void NextPrimLiber(int& primLiber);
	
public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	// daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	int dim() const;

	//verifica daca dictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const;

	int actualizeazaValori(Dictionar& m);


	// destructorul dictionarului	
	~Dictionar();

};