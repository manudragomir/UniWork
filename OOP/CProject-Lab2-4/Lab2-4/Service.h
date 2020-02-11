#pragma once
#include "Repo.h"

/*
functie ce creeaza o masina si o adauga in repository
returneaza 2 daca datele sunt incorecte
		   1 daca masina exista
		   0 daca operatia s-a realizat cu succes
*/
int adauga_masina(Repo* , char*, char*, char*);

/*
functie ce modifica o masina din repository
returneaza 2 daca datele sunt incorecte
		   1 daca masina nu exista
		   0 daca operatia s-a realizat cu succes
*/
int actualizeaza_masina(Repo*, char*, char*, char*);

/*
void inchiriere_masina(); 
*/

/*
O functie ce creeaza o lista noua dupa ce filtreaza elementele din repo
	daca parametrul 3 e 1 - filtreaza dupa categorie
						2 - filtreaza dupa model
	ambele filtrari se fac dupa parametrul 2 de tip string
*/
Vector* filtrare_masina(Repo*, char*, int);

/*
desc: Sorteaza elementele dintr-un repository
in: - un repository
return: un vector sortat
raises: - 
*/
Vector* sortare_masina(Repo*); 


/*
desc: - returneaza o lista cu elementele din vector
in: - un repository
return: pointer la un vector
raises: -
*/
Vector* get_all(Repo* re);