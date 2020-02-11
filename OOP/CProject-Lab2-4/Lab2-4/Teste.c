#include "Teste.h"
#include "Repo.h"
#include "Service.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_creeaza_masina(){
	Masina* m = creeaza_masina("BV-07-VMA", "VW_POLO", "mini");

	char* numar_inm = get_numar_inmatriculare(m);
	char* model = get_model(m);
	char* categorie = get_categorie(m);

	assert(strcmp(numar_inm, "BV-07-VMA") == 0);
	assert(strcmp(model, "VW_POLO") == 0);
	assert(strcmp(categorie, "mini") == 0);

	assert(compara_masina(m, m) == 0);

	free(numar_inm);
	free(model);
	free(categorie);

	distruge_masina(m);
}

void test_adauga_masina() {
	//test de adaugare masina in vector
	Vector* v = creeaza_vector();
	Masina* m = creeaza_masina("BV-07-VMA", "VW_POLO", "mini");
	adauga_vector(v, m, copy_masina);
	assert(len(v) == 1);
	distruge_masina(m);
	distruge_vector(v, distruge_masina);
}


void test_actualizeaza_masina() {
	Repo* re = creeaza_repo(copy_masina, compara_masina, distruge_masina);
	Masina* m = creeaza_masina("BV-07-VMA", "VW_POLO", "mini");
	store_repo(re, m);
	Masina* m1 = creeaza_masina("BV-07-VMA", "VW_PASSAT", "van");
	Masina* m2 = cauta_repo(re, m1);
	assert(m2 != NULL);

	set_masina(m, m1);

	char* model = get_model(m);
	char* categorie = get_categorie(m);

	assert(strcmp(model, "VW_PASSAT") == 0);
	assert(strcmp(categorie, "van") == 0);

	free(model);
	free(categorie);
	distruge_masina(m);
	distruge_masina(m1);
	distruge_repo(re);
}

void test_sort()
{
	Repo *re = creeaza_repo(copy_masina, compara_masina, distruge_masina);
	Masina* m1 = creeaza_masina("hei", "hei", "hei");
	Masina* m2 = creeaza_masina("ba", "ba", "ba");
	Masina* m3 = creeaza_masina("sal", "sal", "sal");
	Masina* m4 = creeaza_masina("key", "key", "key");

	store_repo(re, m1);
	store_repo(re, m2);
	store_repo(re, m3);
	store_repo(re, m4);

	Vector* v = sortare_masina(re);


	Masina* m5 = get_element(v, 0);
	Masina* m6 = get_element(v, 1);
	Masina* m7 = get_element(v, 2);
	Masina* m8 = get_element(v, 3);

	assert(compara_masina(m2, m5) == 0);
	assert(compara_masina(m1, m6) == 0);
	assert(compara_masina(m4, m7) == 0);
	assert(compara_masina(m3, m8) == 0);

	/*
	Omise fiindca get_element intoarce aceeasi referinta, care este distrusa in distruge_vector
	distruge_masina(m5);
	distruge_masina(m6);
	distruge_masina(m7);
	distruge_masina(m8);
	*/
	distruge_masina(m1);
	distruge_masina(m2);
	distruge_masina(m3);
	distruge_masina(m4);
	distruge_vector(v, distruge_masina);
	distruge_repo(re);
}

void test_repo() {
	Repo *re = creeaza_repo(copy_masina, compara_masina, distruge_masina);
	Masina* m = creeaza_masina("sal", "sal", "sal");
	Masina* m1 = creeaza_masina("pa", "pa", "pa");
	int x = store_repo(re, m);
	assert(x == 0);

	x = store_repo(re, m);
	assert(x == 1);

	Masina* z = cauta_repo(re, m);
	assert(z != NULL);

	Masina* y = cauta_repo(re, m1);
	assert(y == NULL);

	Masina* m2 = creeaza_masina("ya", "ya", "ya");
	store_repo(re, m2);

	Vector* v = get_all_elements(re);

	assert(len(v) == 2);
	assert(compara_masina((get_element(v,1)), m2) == 0);
	distruge_vector(v, distruge_masina);
	
	distruge_masina(m2);
	distruge_masina(m1);
	distruge_masina(m);
	distruge_repo(re);
	
}

void test_serv() {
	Repo *re = creeaza_repo(copy_masina, compara_masina, distruge_masina);

	int x = adauga_masina(re, "sal", "sal", "sal");
	assert(x == 0);

	int y = adauga_masina(re, "", "", "");
	assert(y == 2);

	int z = adauga_masina(re, "sal", "sal", "sal");
	assert(z == 1);

	x = actualizeaza_masina(re, "sal", "pa", "pa");
	assert(x == 0);
	
	x = actualizeaza_masina(re, "", "", "");
	assert(x == 2);

	x = actualizeaza_masina(re, "la", "la", "la");
	assert(x == 1);


	Vector* ve = get_all(re);
	assert(len(ve) == 1);

	adauga_masina(re, "salutare", "paparude", "papanas");

	Vector* nv = filtrare_masina(re, "pa", 1);

	assert(len(nv) == 2);

	distruge_vector(nv, distruge_masina);

	Vector* nve = filtrare_masina(re, "papa", 2);

	assert(len(nve) == 1);

	distruge_vector(nve, distruge_masina);
	distruge_vector(ve, distruge_masina);
	distruge_repo(re);

}