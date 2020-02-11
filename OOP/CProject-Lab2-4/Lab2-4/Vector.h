#include "Masina.h"

#pragma once

typedef void* TElem;

typedef struct{
	int lg, capac;
	TElem* elems;
}Vector;

/*
	Functie ce initializeaza o entitate de tip vector
*/
Vector* creeaza_vector();

/*
	Functie ce elibereaza resursele ocupate de entitatea de tip vector si de elementele sale
*/
void distruge_vector(Vector*, void(*distruge_gen_function) (TElem));

/*
	Functie ce adauga o entitate de tip masina in vector
*/
void adauga_vector(Vector*, TElem, TElem(*copiaza_gen_function) (TElem));


/*
	Functie ce returneaza numarul de elemente de tip vector
*/
int len(Vector*);

/*
	Functie ce elibereaza resursele unui vector
*/
void realoca_vector(Vector*);

TElem get_element(Vector*, int);
