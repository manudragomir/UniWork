#include "Service.h"
#include "Masina.h"
#include <string.h>


int adauga_masina(Repo* re, char *s1, char* s2, char* s3)
{
	if (strlen(s1) == 0 || strlen(s2) == 0 || strlen(s3) == 0)
		return 2;

	Masina* m = creeaza_masina(s1, s2, s3);
	int check = store_repo(re, m);
	distruge_masina(m);
	return check;
}

int actualizeaza_masina(Repo* re, char *s1, char *s2, char* s3)
{	
	if (strlen(s1) == 0 || strlen(s2) == 0 || strlen(s3) == 0)
		return 2;

	Masina* m1 = creeaza_masina(s1, s2, s3);
	Masina* m = cauta_repo(re, m1);
	if (m == NULL)
	{
		distruge_masina(m1);
		return 1;
	}

	set_masina(m, m1);
	distruge_masina(m1);
	return 0;
}

Vector* get_all(Repo* re)
{
	return get_all_elements(re);
}

/*
void inchiriere_masina()
{
	return;
}
*/

Vector* filtrare_masina(Repo* re, char* str, int no)
{	
	Vector* ve = get_all_elements(re);
	Vector* new_ve = creeaza_vector();
	
	for (int i = 0; i < len(ve); i++)
		if (no == 1 && strstr(((Masina*)ve->elems[i])->categorie, str) != 0)
			adauga_vector(new_ve, ve->elems[i], copy_masina);
		else if (no == 2 && strstr(((Masina*)ve->elems[i])->model, str) != 0)
			adauga_vector(new_ve, ve->elems[i], copy_masina);

	distruge_vector(ve, distruge_masina);

	return new_ve;
}

void sort_function(Vector* ve, int (*comp_function) (void*, void*))
{
	for (int i = 0; i < len(ve) - 1; i++)
		for (int j = i + 1; j < len(ve); j++)
		{
			if (comp_function(ve->elems[i], ve->elems[j]) > 0)
			{
				void* x = ve->elems[i];
				ve->elems[i] = ve->elems[j];
				ve->elems[j] = x;
			}
		}
}


Vector* sortare_masina(Repo* re)
{
	Vector* ve = get_all_elements(re);
	sort_function(ve, re->comparaFCT);

	return ve;
}