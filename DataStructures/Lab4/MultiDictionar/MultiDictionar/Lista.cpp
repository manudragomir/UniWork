#include "Lista.h"
#include "IteratorLista.h"

Lista::Lista()
{
	this->urm = new int[this->capac];
	this->e = new TValue[this->capac];
	spatiuLiber(0, NMax);
	this->primUsed = -1;
	this->primLiber = 0;
}

vector < TValue > Lista::toVector() const
{
	int current = this->primUsed;
	vector < TValue > v;
	while (current != -1)
	{
		v.push_back(e[current]);
		current = this->urm[current];
	}

	return v;
}

IteratorLista Lista::iterator() const
{
	return IteratorLista(*this);
}

void Lista::spatiuLiber(int st, int fin)
{
	for (int i = st; i < fin - 1; i++)
		this->urm[i] = i + 1;

	this->urm[fin - 1] = -1;
}


void Lista::realoca()
{
	int cap = this->capac * 2;
	int* new_urm = new int[cap];
	TValue* new_e = new TValue[cap];
	for (int i = 0; i < this->capac; i++)
	{
		new_urm[i] = urm[i];
		new_e[i] = e[i];
	}

	this->urm = new_urm;
	this->e = new_e;
	spatiuLiber(this->capac, cap);
	this->capac = this->capac * 2;
}

int Lista::aloca()
{
	int i = this->primLiber;
	if (i == -1)
	{
		realoca();
		i = this->capac / 2;
		this->primLiber = this->urm[i];
	}
	else
	{
		this->primLiber = this->urm[i];
	}
	return i;
}

void Lista::dealoca(int i)
{
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}

void Lista::adauga(TValue v)
{
	int j = aloca();
	this->e[j] = v;
	this->urm[j] = this->primUsed;
	this->primUsed = j;	
}

bool Lista::sterge(TValue v, int& ok)
{
	int current = this->primUsed;
	int prev = -1;

	while (current != -1)
	{
		if (this->e[current] == v)
		{
			if (prev == -1)
			{
				this->primUsed = this->urm[current];
				dealoca(current);
			}

			else
			{
				this->urm[prev] = this->urm[current];
				dealoca(current);
			}

			if (this->primUsed == -1)
				ok = 1;
			return true;
		}
		prev = current;
		current = urm[current];

	}
	return false;
}


Lista::~Lista()
{
	delete[] urm;
	delete[] e;
}
