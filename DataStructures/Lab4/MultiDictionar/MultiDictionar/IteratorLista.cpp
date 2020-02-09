#include "IteratorLista.h"

IteratorLista::IteratorLista(const Lista& c): con(c){
	this->curent = this->con.primUsed;
}

TValue IteratorLista::element()
{
	return this->con.e[this->curent];
}

bool IteratorLista::valid()
{
	return (this->curent != -1);
}

void IteratorLista::urmator()
{
	this->curent = this->con.urm[this->curent];
}

void IteratorLista::prim()
{
	this->curent = this->con.primUsed;
}
