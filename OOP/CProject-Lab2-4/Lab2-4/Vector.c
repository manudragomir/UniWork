#include <stdlib.h>
#include "Vector.h"
#include <string.h>

const int INIT = 1;

Vector* creeaza_vector()
{
	Vector* v = (Vector*)malloc(sizeof(Vector));
	v->lg = 0;
	v->capac = INIT;
	v->elems = malloc(sizeof(TElem) * INIT);
	return v;
}

TElem get_element(Vector *v, int poz)
{
	return v->elems[poz];
}


void distruge_vector(Vector *v, void (*distruge_gen_function) (TElem))
{	
	for (int i = 0; i < v->lg; i++) {
		distruge_gen_function(v->elems[i]);
	}
	
	free(v->elems);
	free(v);
	
}

void realoca_vector(Vector* v) {
	int new_size = v->capac * 2;
	TElem* new_vec = malloc(sizeof(TElem) * new_size);
	for (int i = 0; i < v->lg; i++)
		new_vec[i] = v->elems[i];

	free(v->elems);
	v->elems = new_vec;
	v->capac = new_size;
}

void adauga_vector(Vector* v, TElem m, TElem (*copiaza_gen_function) (TElem))
{
	TElem m2 = copiaza_gen_function(m);

	if (v->lg == v->capac)
		realoca_vector(v);

	v->elems[v->lg] = m2;
	v->lg++;
}

int len(Vector *v)
{
	return v->lg;
}