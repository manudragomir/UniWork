#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <stdio.h>
#include <assert.h>

#include "Service.h"
#include "Masina.h"
#include "Vector.h"
#include "Teste.h"
#include "Repo.h"

void run_tests()
{
	test_actualizeaza_masina();
	test_creeaza_masina();
	test_adauga_masina();
	test_repo();
	test_serv();
	test_sort();
	printf("Toate testele merg!!!\n");
	return;
}

void UIadauga_masina(Repo* re)
{
	char str1[100];
	char str2[100];
	char str3[100];
	printf("Numar inmatriculare: ");
	scanf("%s", str1);
	getchar();

	printf("Model: ");
	scanf("%s", str2);
	getchar();

	printf("Categorie: ");
	scanf("%s", str3);

	int nr = adauga_masina(re, str1, str2, str3);
	if(nr == 0)
	{
		printf("COMANDA EFECTUATA CU SUCCES\n");
	}

	else if (nr == 1)
	{
		printf("EXISTA DEJA!\n");
	}

	else
	{
		printf("DATE INVALIDE!\n");
	}

}

void UIactualizeaza_masina(Repo *re)
{
	char str1[100];
	char str2[100];
	char str3[100];

	printf("Modifici masina cu nr de inmatriculare: ");
	scanf("%s", str1);
	getchar();

	printf("Model: ");
	scanf("%s", str2);
	getchar();

	printf("Categorie: ");
	scanf("%s", str3);

	int nr = actualizeaza_masina(re, str1, str2, str3);

	if (nr == 0)
	{
		printf("COMANDA EFECTUATA CU SUCCES\n");
	}

	else if (nr == 1)
	{
		printf("NU EXISTA ELEMENTUL DE ACTUALIZAT!\n");
	}

	else
	{
		printf("DATE INVALIDE!\n");
	}

}

void UIvizualizare_masina(Repo* re)
{
	int mod;
	printf("1 - Categorie\n2 - Model\n");
	scanf("%d", &mod);
	
	char str[100];
	printf("De cautat: ");
	scanf("%s", str);

	if (mod != 1 && mod != 2)
	{
		printf("Mai incearca!");
		return;
	}

	Vector* v = filtrare_masina(re, str, mod);

	for (int i = 0; i < len(v); i++)
	{
		print_masina(v->elems[i]);
	}

	distruge_vector(v, distruge_masina);
	return;
}

/*
void UIstergere_masina(Repo* re)
{
	char str[10];

	printf("Numar inmatriculare: ");
	scanf("%s", str);
	
	int x = stergere_masina(re);
}
*/

void UIsortare_masina(Repo* re)
{
	Vector* v = sortare_masina(re);
	for (int i = 0; i < len(v); i++)
	{
		print_masina(v->elems[i]);
	}
	distruge_vector(v, distruge_masina);
}

void UIafisare(Vector* v)
{
	int i;
	for (i = 0; i < len(v); i++)
	{
		print_masina(v->elems[i]);
	}
}

int main()
{	
	run_tests();
	char menu[200] = "0: Exit\n1: Adauga masina\n2: Actualizeaza masina\n3: Vizualizare masini\n4: Sort Masina\n5: Afisare\n7:Stergere";
	
	Repo *re = creeaza_repo(copy_masina, compara_masina, distruge_masina);

	while (1)
	{
		puts(menu);
		int cmd = 0;
		printf("Comanda nr: ");
		scanf("%d", &cmd);
		if (cmd == 0)
			break;

		switch (cmd) {
		case 1: UIadauga_masina(re); break;
		case 2: UIactualizeaza_masina(re); break;
		case 3: UIvizualizare_masina(re); break;
		case 4: UIsortare_masina(re); break;
		case 5: UIafisare(re->repo); break;
		}

	}

	distruge_repo(re);
	int gata;
	scanf("%d", &gata);
	_CrtDumpMemoryLeaks();
	return 0;
	
}