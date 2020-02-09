#include "IteratorMD.h"

//theta(1) toate

IteratorMD::IteratorMD(const MD& c) : con(c) {
	this->curentKey = this->con.primUsed;
	this->curentValue = this->con.e[curentKey].second.primUsed;
}

TElem IteratorMD::element() {
	//TBA
	//return { this->con.e[this->curentKey].first, this->con.};
	return { this->con.e[curentKey].first, this->con.e[curentKey].second.e[curentValue] };
}

bool IteratorMD::valid() {
	//TBA
	return (this->curentKey != -1);
}

void IteratorMD::urmator() {
	//TBA

	this->curentValue = this->con.e[curentKey].second.urm[curentValue];
	if (this->curentValue == -1)
	{
		this->curentKey = this->con.urm[curentKey];
		this->curentValue = this->curentValue = this->con.e[curentKey].second.primUsed;
	}
}

void IteratorMD::prim() {
	
	this->curentKey = this->con.primUsed;
	this->curentValue = this->con.e[curentKey].second.primUsed;
}
