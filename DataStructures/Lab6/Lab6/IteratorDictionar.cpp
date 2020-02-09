#include "IteratorDictionar.h"
#include <algorithm>

void IteratorDictionar::prim()
{
	position = -1;
	urmator();
}

void IteratorDictionar::urmator()
{
	position++;

	while (position < this->d.m && d.ch[position].first == NULL_TCHEIE)
		position++;
}

bool IteratorDictionar::valid() const
{
	if (position == this->d.m)
		return false;
	return true;
}

TElem IteratorDictionar::element() const
{
	TCheie cheie = d.ch[position].first;
	TValoare val = d.ch[position].second;
	return { cheie,val };
}
