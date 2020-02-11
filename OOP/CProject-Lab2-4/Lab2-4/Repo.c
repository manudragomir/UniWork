#include "Repo.h"
#include "Vector.h"
#include "Masina.h"
#include <stdlib.h>

Repo* creeaza_repo(Masina* (*copy_gen_masina) (Masina*),  int(*compara_gen_masina) (Masina*, Masina*), void(*distruge_gen_masina) (Masina*) )
{
	Repo *re = malloc(sizeof(Repo));
	re->repo = creeaza_vector();

	re->copyFCT = copy_gen_masina;
	re->comparaFCT = compara_gen_masina;
	re->distrugeFCT = distruge_gen_masina;

	return re;
}

int store_repo(Repo* re, Masina* m)
{
	Masina* x = cauta_repo(re, m);

	if (x != NULL)
		return 1;

	adauga_vector(re->repo, m, re->copyFCT);
	return 0;
}

Masina* cauta_repo(Repo* re, Masina* m)
{
	for (int i = 0; i < re->repo->lg; i++)
		if (re->comparaFCT(re->repo->elems[i], m) == 0)
			return re->repo->elems[i];

	return NULL;
}

Vector* get_all_elements(Repo* re) {

	Vector* ve = creeaza_vector();
	
	for (int i = 0; i < len(re->repo); i++) {
		adauga_vector(ve, (re->repo->elems[i]), re->copyFCT);
	}

	return ve;
}

void distruge_repo(Repo *re)
{
	distruge_vector(re->repo, re->distrugeFCT);
	free(re);
}