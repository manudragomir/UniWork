#include "LI.h"
#include "IteratorLI.h"
#include <iostream>

// aici implementarea operatiilor din LI.h



LI::LI() {
	this->dimen = 0;
	this->prim = NULL;
	this->ultim = NULL;
}

int LI::dim() const
{
	return this->dimen;
}

//theta(1)
bool LI::vida() const
{
	if (this->dimen == 0)
		return true;
	return false;
}

//O(N)
TElem LI::element(int i) const
{
	if (i >= this->dimen)
		throw std::exception("eroare");

	node* fake_iter = this->prim;
	int count = 0;
	while (count != i)
	{
		fake_iter = fake_iter->next;
		count += 1;
	}

	return fake_iter->info;
}

//O(N)
TElem LI::modifica(int i, TElem e)
{
	if (i >= this->dimen || i<0)
		throw std::exception("eroare");

	node* fake_iter = this->prim;
	int count = 0;
	while (count != i)
	{
		fake_iter = fake_iter->next;
		count += 1;
	}

	TElem old_elem = fake_iter->info;
	fake_iter->info = e;
	return old_elem;
}

//theta(1)
void LI::adaugaSfarsit(TElem e)
{
	if (this->dimen == 0)
	{
		this->prim = creeazaNod(e);
		this->ultim = this->prim;
	}

	else
	{
		node* nod = creeazaNod(e);
		nod->prev = this->ultim;
		nod->next = NULL;
		this->ultim->next = nod;
		this->ultim = nod;
	}

	this->dimen += 1;
}

//O(N)
void LI::adauga(int i, TElem e)
{
	TElem sters;

	if (i >= this->dimen)
		throw std::exception("eroare");

	if (i == 0)
	{
		node* nou = creeazaNod(e);
		nou->prev = NULL;
		nou->next = this->prim;
		this->prim = nou;
		this->dimen += 1;
		return;
	}

	else if (i==this->dimen - 1)
	{
		adaugaSfarsit(e);
		return;
	}

	node* fake_iter = this->prim;
	TElem val;
	int count = 0;
	while (count != i)
	{
		fake_iter = fake_iter->next;
		count += 1;
	}

	node* nou = creeazaNod(e);
	fake_iter->prev->next = nou;
	nou->prev = fake_iter->prev;

	nou->next = fake_iter;
	fake_iter->prev = nou;
	this->dimen += 1;
}

//O(N)
TElem LI::sterge(int i)
{
	TElem sters;

	if (i >= this->dimen)
		throw std::exception("eroare");

	if (i == 0)
	{
		node* nod = this->prim->next;
		TElem val = this->prim->info;
		delete this->prim;
		this->prim = nod;
		this->dimen -= 1;
		return val;
	}

	else if (i == this->dimen - 1)
	{
		node* nod = this->ultim->prev;
		TElem val = this->ultim->info;
		delete this->ultim;
		this->ultim = nod;
		this->ultim->next = NULL;
		this->dimen -= 1;
		return val;
	}

	node* fake_iter = this->prim;
	TElem val;
	int count = 0;
	while (count != i)
	{
		fake_iter = fake_iter->next;
		count += 1;
	}

	fake_iter->next->prev = fake_iter->prev;
	fake_iter->prev->next = fake_iter->next;
	val = fake_iter->info;
	delete fake_iter;
	this->dimen -= 1;
	return val;
}

//O(N)
int LI::cauta(TElem e) const
{
	node* fake_iter = this->prim;
	int i = 0;
	while (fake_iter != NULL && fake_iter->info != e)
	{
		fake_iter = fake_iter->next;
		i += 1;
	}

	if (fake_iter == NULL)
		return -1;

	return i;

}

IteratorLI LI::iterator() const
{
	return IteratorLI(*this);
}

int LI::eliminaToate(LI& lista)
{
	int contor = 0;

	//N lungimea listei ca parametru
	//M lungimea listei
	for (int i = 0; i < lista.dim(); i++) //theta(N)
	{
		TElem elem = lista.element(i); // theta(i)
		int pozitie = this->cauta(elem); // O(M)
		if (pozitie != -1)
		{
			contor += 1;
			this->sterge(pozitie); //O(M)
		}
	}

	return contor;
}

/*
IteratorLI LI::iterator() const {
	return IteratorLI(*this);
}
*/

//theta(N)
LI::~LI() {
	node* curent = this->prim;
	while (curent != NULL)
	{
		node* next = curent->next;
		delete curent;
		curent = next;
	}
}


// restul operatiilor