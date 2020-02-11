#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Masina.h"

/*
desc: Functie ce creeaza o masina, alocand spatiu dinamic
in: numar,model,categorie - 3 string-uri
raises: -
return: un pointer la o entitate de tip masina
*/
Masina* creeaza_masina(char *numar, char *model, char *categorie){
	Masina* m = (Masina*)malloc(sizeof(Masina));

	m->numar = (char*)malloc(strlen(numar) + 1);
	m->model = (char *)malloc(strlen(model) + 1);
	m->categorie = (char*)malloc(strlen(categorie) + 1);

	strcpy_s(m->numar, strlen(numar) + 1, numar);
	strcpy_s(m->model, strlen(model) + 1, model);
	strcpy_s(m->categorie, strlen(categorie) + 1, categorie);

	return m;
}

/*
desc: Functie ce copiaza o masina, asemenea unui constructor de copiere
in: un pointer la o entitate de tip masina
raises: -
return: un pointer la o entitate de tip masina nou 'construita'/alocata
*/
Masina* copy_masina(Masina *m)
{
	Masina* m2 = (Masina*)malloc(sizeof(Masina));

	m2->numar = (char*)malloc(strlen(m->numar) + 1);
	m2->model = (char *)malloc(strlen(m->model) + 1);
	m2->categorie = (char*)malloc(strlen(m->categorie) + 1);

	strcpy_s(m2->numar, strlen(m->numar) + 1, m->numar);
	strcpy_s(m2->model, strlen(m->model) + 1, m->model);
	strcpy_s(m2->categorie, strlen(m->categorie) + 1, m->categorie);
	return m2;
}

/*
desc: functie ce elibereaza resursele unei entitati de tip masina(3 string-uri si spatiul destinat pointerului 
	  la masina)
in: un pointer la o entitate de tip masina
raises: -
return: -
*/
void distruge_masina(Masina* m) {
	free(m->numar);
	free(m->model);
	free(m->categorie);
	free(m);
}


void print_masina(Masina* m){	
	printf("%s %s %s\n", m->numar, m->model, m->categorie);
}

char* get_numar_inmatriculare(Masina* m) {
	char* str = (char*)malloc(strlen(m->numar) + 1);
	strcpy_s(str, strlen(m->numar) + 1, m->numar);

	return str;
}

char* get_model(Masina* m) {
	char* str = (char*)malloc(strlen(m->model) + 1);
	strcpy_s(str, strlen(m->model) + 1, m->model);

	return str;
}

char* get_categorie(Masina* m) {
	char* str = malloc(strlen(m->categorie) + 1);
	strcpy_s(str, strlen(m->categorie) + 1, m->categorie);

	return str;
}


int compara_masina(Masina* m1, Masina *m2){
	return strcmp(m1->numar, m2->numar);
}


void set_masina(Masina* m1, Masina* m2){
	char* str1 = m1->categorie;
	char* str2 = m1->model;

	m1->model = (char *)malloc(strlen(m2->model) + 1);
	m1->categorie = (char*)malloc(strlen(m2->categorie) + 1);

	strcpy_s(m1->model, strlen(m2->model) + 1, m2->model);
	strcpy_s(m1->categorie, strlen(m2->categorie) + 1, m2->categorie);

	free(str1);
	free(str2);
}
