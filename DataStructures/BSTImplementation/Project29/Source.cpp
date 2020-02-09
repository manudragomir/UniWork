#include <iostream>

using namespace std;

template <typename T>
struct node{
	T info;
	node* st;
	node* dr;
	node* parinte;
};

template <typename T>
class ABC
{
	node<T>* rad;
	node<T>* adauga_rec(node<T>* p, T elem) {
		if (p == NULL) {
			auto nod = new node<T>;
			nod->info = elem;
			nod->st = nod->dr = nod->parinte = NULL;
			return nod;
		}
		else {
			if (p->info < elem) {
				p->dr = adauga_rec(p->dr, elem);
				p->dr->parinte = p;
			}
			else {
				p->st = adauga_rec(p->st, elem);
				p->st->parinte = p;
			}

			return p;
		}
	}
public:
	ABC<T>() {
		rad = NULL;
	}

	T parint(T elem) {
		auto nod = cauta(elem);
		return nod->parinte->info;
	}
	ABC<T>& adauga(T elem) {
		rad = adauga_rec(rad, elem);
		return *this;
	}
	node<T>* cauta(T elem) {
		auto p = rad;
		while (p != NULL && p->info != elem) {
			if (elem < p->info) {
				p = p->st;
			}
			else {
				p = p->dr;
			}
		}
		return p;
	}
	ABC<T>& add(T elem) {
		node<T>* prev = NULL;
		auto p = rad;
		auto last = 0;
		while (p != NULL) {
			prev = p;
			if (p->info < elem) {
				p = p->dr;
				last = 1;
			}
			else {
				p = p->st;
				last = 0;
			}
		}

		auto nod = new node<T>;
		nod->st = NULL;
		nod->dr = NULL;
		nod->info = elem;
		if (prev == NULL) {
			rad = nod;
		}
		else {
			if (last == 0) {
				prev->st = nod;
			}
			else {
				prev->dr = nod;
			}
		}

		return *this;
	}

	node<T>* minim(node<T>* subArb) {
		auto p = subArb;
		while (p->st != NULL) {
			p = p->st;
		}
		return p;
	}

	node<T>* maxim(node<T>* subArb) {

		auto p = subArb;
		while (p->dr != NULL) {
			p = p->dr;
		}
		return p;
	}

	node<T>* parinte(node<T>* act) {
		auto p = rad;
		node<T>* prec = NULL;
		while (p != NULL && p != act) {
			prec = p;
			if (act->info < p->info) {
				p = p->st;
			}
			else {
				p = p->dr;
			}
		}
		return prec;
	}

	node<T>* succesor(node<T>* p) {
		if (p->dr != NULL) {
			return minim(p->dr);
		}

		auto prec = parinte(p);
		while (prec != NULL && p == prec->dr) {
			p = prec;
			prec = parinte(p);
		}

		return prec;
	}

	node<T>* predecesor(node<T>* p) {
		if (p->st != NULL) {
			return maxim(p->st);
		}

		auto prec = parinte(p);
		while (prec != NULL && p == prec->st) {
			p = prec;
			prec = parinte(p);
		}

		return prec;
	}

	void sterge(T cheie) {
		auto p = rad;
		node<T>* prec = NULL;
		while (p != NULL) {
			if (cheie < p->info) {
				prec = p;
				p = p->st;
			}
			else if (cheie > p->info) {
				prec = p;
				p = p->dr;
			}
			else {
				if (p->st != NULL && p->dr != NULL) {
					auto el = minim(p->dr);
					p->info = el->info;
					prec = p;
					p = p->dr;
					cheie = p->info;
				}
				else if (p->st == NULL) {	
					if (prec == NULL) {
						auto deSters = p;
						rad = p->dr;
						delete deSters;
					}
					else {
						auto deSters = p;
						if (p == prec->st) {
							prec->st = p->dr;
						}
						else {
							prec->dr = p->dr;
						}
						delete deSters;

					}
					p = NULL;
				}
				else if (p->dr == NULL) {
					if (prec == NULL) {
						auto deSters = p;
						rad = p->st;
						delete deSters;
					}
					else {
						auto deSters = p;
						if (p == prec->st) {
							prec->st = p->st;
						}
						else {
							prec->dr = p->st;
						}
						delete deSters;
					}
					p = NULL;
				}
			}
		}
	}
};

int main()
{
	ABC<int> a;
	a.adauga(5).adauga(7).adauga(3).adauga(1).adauga(-5).adauga(12).adauga(22).adauga(6).adauga(8).adauga(2);
	cout << a.parint(12);
	return 0;
}