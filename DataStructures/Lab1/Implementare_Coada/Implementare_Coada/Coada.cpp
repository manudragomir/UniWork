 #include "Coada.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


Coada::Coada()
{
	this->capac = len;
	this->size = 0;
	this->front = 0;
	this->back = -1;
	queue = new TElem[this->capac];
	//queue = new TElem[(this->capac)*sizeof(TElem)];
}

void Coada::adauga(TElem e)
{
	if (this->plina() == true)
	{
		int new_capac = 2 * this->capac;
		TElem* queue2 = new TElem[new_capac * sizeof(TElem)];

		if (this->back < this->front)
		{
			for (int i = 0; i < this->back; i++)
				queue2[i] = this->queue[i];

			for (int i = this->front; i < this->capac; i++)
				queue2[i + this->capac] = this->queue[i];
		}

		else
		{	
			for (int i = 0; i < this->capac; i++)
				queue2[i] = this->queue[i];

		}
		delete[] this->queue;
		this->queue = queue2;

		this->front += this->capac;
		this->capac = new_capac;


	}

	this->back = (this->back + 1) % this->capac;
	this->queue[this->back] = e;
	this->size += 1;
}

TElem Coada::element() const
{
	if (this->vida() == true)
		throw 0;

	return this->queue[this->front];
}

TElem Coada::sterge()
{
	if (this->vida() == true)
		throw 0;

	TElem item = this->queue[this->front];
	this->front = (this->front + 1) % this->capac;
	this->size -= 1;
	
	return item;

}

bool Coada::vida() const
{
	if (this->size == 0)
		return true;
	return false;
}

bool Coada::plina() const
{
	if (this->size == this->capac)
		return true;
	return false;
}


Coada::~Coada()
{
	delete[] queue;
}
