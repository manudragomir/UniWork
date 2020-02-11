#pragma once

typedef struct
{
	char *numar;
	char *model;
	char *categorie;
} Masina;

/*
desc: constructorul entitatii de tip masina
in: 3 strings
raises: -
return: pointer la masina
*/
Masina* creeaza_masina(char*, char*, char*);

/*
desc: copy constructor
in: pointer la masina
raises: -
return: pointer la o masina cu aceleasi valori ale campurilor
*/
Masina* copy_masina(Masina *m);

/*
desc: primeste o masina si elibereaza resursele alocate pentur ea
in: pointer la masina
raises: -
return: -
*/
void distruge_masina(Masina*);

/*
desc: Functie ce primeste o masina si ii returneaza numarul de inmatriculare, creand un nou numar de inmatriculare
in: o entitate de tip masina
raises: -
return: un string
*/
char* get_numar_inmatriculare(Masina*);

/*
desc: Functie ce primeste o masina si ii returneaza modelul, creand un nou model
in: o entitate de tip masina
raises: -
return: un string
*/
char* get_model(Masina*);

/*
desc: Functie ce primeste o masina si ii returneaza categoria, creand o noua categorie
in: o entitate de tip masina
raises: -
return: un string
*/
char* get_categorie(Masina*);

/*
desc: Functie ce primeste doua masini si le compara dupa numarul de inmatriculare(care ar trebui sa fie unic determinat)
in: doua entitati de tip masina
raises: -
return: <0 daca e mai mic
		=0 daca-s la fel
		>0 daca e mai mare lexicografic numarul primei masini
*/
int compara_masina(Masina*, Masina*);

/*
desc: Functie ce se ocupa cu printarea unei entitati complexe de tip masina
*/
void print_masina(Masina*);

/*
desc: Functie ce primeste o masina si ii seteaza categoria si modelul in functie de masina2, resursele fiind
	  eliberate de apelant
in: doua entitati de tip masina
raises: -
return: -
*/
void set_masina(Masina*, Masina*);