#pragma once
#include "MD.h"
#include "defs.h"
#include "IteratorLista.h"
#include <vector>

using std::vector;

class MD;

class IteratorMD
{
	friend class MD;
	friend class IteratorLista;
	

private:
	//iteratorul memoreaza o referinta catre MD
	const MD& con;
	//aici alte atribute specifice: curent, etc
	IteratorMD(const MD& c);

	int curentKey;
	int curentValue;

public:
	TElem element();
	bool valid();
	void urmator();
	void prim();
};
