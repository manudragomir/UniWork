#include "Dictionar.h"
#include <algorithm>
#include "IteratorDictionar.h"

using namespace std;


void Dictionar::Rehashing()
{

	int mvechi = m;
	m = v[index++];

	TElem * nr = new TElem[mvechi];
	for (int i = 0; i < mvechi; i++)
		nr[i] = ch[i];

	delete[] ch;
	delete[] urm;
	ch = new TElem[m];
	urm = new int[m];
	dimen = 0;
	for (int i = 0; i < m; i++) {
		urm[i] = -1;
		ch[i].first = NULL_TCHEIE;
		ch[i].second = NULL_TVALOARE;
	}

	for (int i = 0; i < mvechi; i++)
		adauga(nr[i].first, nr[i].second);

	delete[] nr;
	primLiber = -1;
}

void Dictionar::NextPrimLiber(int & primLiber)
{
	primLiber++;

	while (primLiber < m && ch[primLiber].first != NULL_TCHEIE)
		primLiber++;
}

Dictionar::Dictionar()
{
	dimen = 0;
	index = 0;
	m = v[index++];
	primLiber = -1;
	ch = new TElem[m];
	urm = new int[m];

	for (int i = 0; i < m; i++){
		urm[i] = -1;
		ch[i].first = NULL_TCHEIE;
		ch[i].second = NULL_TVALOARE;
	}

}

TValoare Dictionar::adauga(TCheie c, TValoare v)
{
	if (dimen == m)
		Rehashing();

	int position = d(c);

	//daca nu-i nimic inca
	if (ch[position].first == NULL_TCHEIE) {
		//adaugam elementul si returnam ca nu era nimic
		dimen++;
		ch[position].first = c;
		ch[position].second = v;
		return NULL_TVALOARE;
	}

	//cautam sa vedem daca exista cheia, incepand de la positia la care trebuia pus
	//si mergem pe lista, se opreste pe ultima pozitie

	int prev = -1;
	while (position != -1 && ch[position].first != c) {
		prev = position;
		position = urm[position];
	}

	//exista cheia
	if (position != -1 && ch[position].first == c) {
		TValoare val = ch[position].second;
		ch[position].second = v;
		return val;
	}


	NextPrimLiber(primLiber);

	//daca nu e capul listei
	if (prev != -1) {
		urm[prev] = primLiber;
	}

	ch[primLiber].first = c;
	ch[primLiber].second = v;
	dimen++;
	return NULL_TVALOARE;
}

TValoare Dictionar::cauta(TCheie c) const
{
	int position = d(c);
	while (position != -1 && ch[position].first != c){
		position = urm[position];
	}

	if(position == -1)
		return NULL_TVALOARE;
	
	return ch[position].second;
}

TValoare Dictionar::sterge(TCheie c)
{
	TValoare val = cauta(c);
	if (val == NULL_TVALOARE)
		return NULL_TVALOARE;

	int prev_i = -1;
	int i = d(c);

	while (ch[i].first != c) {
		prev_i = i;
		i = urm[i];
	}

	val = ch[i].second;
	bool gata = false;
	int j, prev_j;

	while (!gata) {
		j = urm[i];
		prev_j = i;

		while (j != -1 && d(ch[j].first) != i) {
			prev_j = j;
			j = urm[j];
		}

		if (j == -1) {
			gata = true;
		}

		else {
			ch[i].first = ch[j].first;
			ch[i].second = ch[j].second;
			urm[i] = urm[j];
			i = j;
			prev_i = prev_j;
		}
	}

	if (prev_i != -1) {
		urm[prev_i] = urm[i];
	}

	ch[i].first = NULL_TCHEIE;
	ch[i].second = NULL_TVALOARE;
	urm[i] = -1;
	
	if (i < primLiber) {
		primLiber = i-1;
	}

	--dimen;
	return val;
}

int Dictionar::dim() const
{
	return dimen;
}

bool Dictionar::vid() const
{
	return (dimen == 0);
}

IteratorDictionar Dictionar::iterator() const
{
	return IteratorDictionar(*this);
	//return IteratorDictionar();
}

int Dictionar::actualizeazaValori(Dictionar& m)
{
	int count = 0;
	TElem e;
	IteratorDictionar id = m.iterator();
	id.prim();
	while (id.valid()) {
		e = id.element();
		TCheie c = e.first;
		TValoare v = e.second;
		TValoare rez = cauta(c);
		if (rez != NULL_TVALOARE && rez != v)
		{
			//daca am gasit cheia si daca valoarea asociata cheii difera
			++count;
			adauga(c, v);
		}
		id.urmator();
	}

	return count;
}

Dictionar::~Dictionar()
{
	delete[] urm;
	delete[] ch;
}
