#pragma once
#include <string>
#include <istream>

using std::string;
using std::istream;

class Echipa
{
private:
	string nume;
	double atac;
	double mij;
	double ap;
	string tara;
public:
	Echipa() {};
	Echipa(string nume, double atac, double mij, double ap, string tara) :
		nume{ nume }, atac{ atac }, mij{ mij }, ap{ ap }, tara{ tara } {};
	string getNume() const {
		return nume;
	}
	double getAtac() const {
		return atac;
	}
	double getMij() const {
		return mij;
	}
	double getAp() const {
		return ap;
	}
	string getTara() const {
		return tara;
	}
	friend istream& operator>>(istream& is, Echipa& ec) {
		//overload functia de citire
		is >> ec.nume >> ec.atac >> ec.mij >> ec.ap >> ec.tara;
		return is;
	}
	~Echipa() {};
};

