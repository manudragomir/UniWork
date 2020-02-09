#include "MD.h"
#include <algorithm>

void MD::spatiuLiber(int st, int fin)//theta(n)
{
	for (int i = st; i < fin - 1; i++)
		this->urm[i] = i + 1;

	this->urm[fin - 1] = -1;
}

void MD::realoca()//theta(n)
{
	int cap = this->capac * 2;
	int* new_urm = new int[cap];
	std::pair<TCheie, Lista>* new_e = new std::pair<TCheie,Lista>[cap];
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

int MD::aloca()//theta(1) amortizat
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

void MD::dealoca(int i)//theta(1)
{
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}


MD::MD()//theta(1)
{
	this->urm = new int[this->capac];
	this->e = new std::pair<TCheie,Lista>[this->capac];
	spatiuLiber(0, NMax);
	this->primUsed = -1;
	this->primLiber = 0;
	this->lungime = 0;
}

void MD::adauga(TCheie c, TValoare v)//O(chei)
{
	if (this->cauta(c).size() == 0)
	{
		int j = aloca();
		this->e[j].first = c;
		this->e[j].second.adauga(v);
		this->urm[j] = this->primUsed;
		this->primUsed = j;
	}

	else
	{
		int current = this->primUsed;
		while (current != -1)//O(chei)
		{
			if (this->e[current].first == c)
			{
				this->e[current].second.adauga(v);//theta(1) amortizat
				break;
			}

			current = urm[current];
		}
	}

	lungime++;

}

vector<TValoare> MD::cauta(TCheie c) const//O(chei)
{
	int current = this->primUsed;
	while (current != -1)
	{
		if (this->e[current].first == c)
		{
			//return this->e[current].second;
			return this->e[current].second.toVector();
		}

		current = urm[current];
	}
	vector < TValoare > v{};
	return v;
}

bool MD::sterge(TCheie c, TValoare v)
{
	if (this->cauta(c).size() == 0)
		return false;
	
	int current = this->primUsed;
	int prev = -1;

	while (current != -1)//O(chei)
	{
		if (this->e[current].first == c)
		{
			int ok{ 0 };
			bool value = this->e[current].second.sterge(v, ok);//O(nr_valori)
			if (value == true)
				lungime--;

			if (ok == 1)
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
			}
			return value;
		}

		prev = current;
		current = urm[current];
		
	}

	return false;
}

int MD::dim() const
{
	return lungime;
}

bool MD::vid() const
{
	if (this->primUsed == -1)
		return true;
	return false;
}

IteratorMD MD::iterator() const
{
	return IteratorMD(*this);
}


int MD::adaugaInexistente(MD& md)
{
	int nr_adaugate{ 0 };
	IteratorMD it = md.iterator();
	while (it.valid())
	{
		TElem el = it.element();
		TCheie cheia = el.first;
		TValoare val = el.second;
		vector < TValoare > vec = this->cauta(cheia);
		int ok = 0;
		for (auto iterator : vec)
		{
			if (iterator == val)
			{
				ok = 1;
			}

			if (ok == 1)
				break;
		}
		if (ok == 0)
		{
			this->adauga(cheia, val);
			nr_adaugate++;
		}
		it.urmator();
	}

	return nr_adaugate;
}


MD::~MD()
{
	delete[] e;
	delete[] urm;
}
