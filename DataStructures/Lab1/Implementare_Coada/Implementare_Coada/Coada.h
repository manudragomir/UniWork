//Coada.h

typedef int TElem;
const int len = 4;

class Coada {
private:
	TElem* queue;
	int size;
	int front;
	int back;
	int capac;

public:
	//constructorul implicit
	Coada();

	//adauga un element in coada
	void adauga(TElem e);

	//acceseaza elementul cel mai devreme introdus in coada 
	//arunca exceptie daca coada e vida
	TElem element() const;

	//sterge elementul cel mai devreme introdus in coada si returneaza elementul sters (principiul FIFO)
	//arunca exceptie daca coada e vida
	TElem sterge();

	//verifica daca coada e vida;
	bool vida() const;

	bool plina() const;


	// destructorul cozii
	~Coada();

};
