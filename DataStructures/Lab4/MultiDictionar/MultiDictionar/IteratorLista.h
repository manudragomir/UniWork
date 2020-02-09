#pragma once
#include "Lista.h"

class Lista;
typedef int TValue;

class IteratorLista
{
	friend class Lista;
	friend class IteratorMD;
	int curent;

private:
	//iteratorul memoreaza o referinta catre MD
	const Lista& con;
	//aici alte atribute specifice: curent, etc

	IteratorLista(const Lista& c);

public:
	TValue element();
	bool valid();
	void urmator();
	void prim();
};
