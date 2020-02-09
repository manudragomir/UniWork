#pragma once
#include "LI.h"

class LI;

typedef int TElem;

class IteratorLI
{
	friend class LI;

private:
	//iteratorul memoreaza o referinta catre LI
	const LI& con;
	//aici alte atribute specifice: curent, etc
	IteratorLI(const LI& c);
	int value;

public:
	TElem element();
	bool valid();
	void urmator();
	void prim();
};
