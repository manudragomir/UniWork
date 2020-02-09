#pragma once
#include "IteratorMDO.h"
#include <algorithm>
#include <vector>


using std::vector;

typedef int TCheie;
typedef int TValoare;
typedef std::pair<TCheie, TValoare> TElem;

typedef bool(*Relatie)(TCheie, TCheie);

class IteratorMDO;

struct Node {
	TCheie info;
	Node* left;
	Node* right;
	Node() {
		left = nullptr;
		right = nullptr;
	};
	vector < TValoare > values;
	Node(TCheie _info) : info{ _info } {
		left = nullptr;
		right = nullptr;
	}
	Node(TCheie _info, Node* _left, Node* _right) : info{ _info }, left{ _left }, right{ _right } {};
};

class MDO {
	friend class IteratorMDO;
private:
	/* aici e reprezentarea */
	int size;
	Relatie R;
	Node* root;
	Node* cauta_iterativ(Node* nod, TCheie c) const;
	Node* adauga_recursiv(Node* nod, TCheie c, TValoare v);
	Node* sterge_recursiv(Node* nod, TCheie c, TValoare v, bool& sters);
	Node* minim(Node* nod);
public:
	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile ordine dupa relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO() {};

};
