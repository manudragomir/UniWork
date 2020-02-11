#include "Vector.h"
#pragma once

typedef struct
{
	Vector* repo;
	TElem (*copyFCT)(TElem);
	int (*comparaFCT)(TElem, TElem);
	void(*distrugeFCT)(TElem);
}Repo;

/*
functie ce creeaza un repo
*/
Repo* creeaza_repo(Masina* (*copy_gen_masina) (Masina*), int(*compara_gen_masina) (Masina*, Masina*), void(*distruge_gen_masina) (Masina*));

/*
functie ce adauga in repo
*/
int store_repo(Repo*, Masina*);

/*
functie ce distrugeun repo
*/
void distruge_repo(Repo*);

/*
functie ce cauta in repo
*/
Masina* cauta_repo(Repo*, Masina*);

/*
functie ce ia toate elementele din repo si le returneaza
*/
Vector* get_all_elements(Repo* re);

