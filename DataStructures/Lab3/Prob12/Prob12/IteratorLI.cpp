#include "IteratorLI.h"
#include "LI.h"
#include <exception>

IteratorLI::IteratorLI(const LI& c) : con(c) {
	// initializare curent si alte atribute specifice
	this->value = 0;
}

TElem IteratorLI::element() {
	if (this->valid() != true)
		throw std::exception("eroare");
	return this->con.element(this->value);
}

bool IteratorLI::valid() {
	//TBA
	if (this->value < con.dimen)
		return true;
	return false;
}

void IteratorLI::urmator() {
	if (this->valid() != true)
		throw std::exception("eroare");
	this->value += 1;
}

void IteratorLI::prim() {
	//TBA
	this->value = 0;
}
