#include <iostream>
#include "Coada.h"
//#include "IteratorContainer.h"
#include <assert.h>

using namespace std;

void testCreeaza() {
	Coada c;
	assert(c.vida() == true);
	try {
		c.element(); //daca e vida ar trebui sa arunce exceptie
		assert(false); //daca nu a aruncat exceptie, vrem sa avem un assert care da fail
	}
	catch (int e) {
		assert(true);
	}
	try {
		c.sterge(); //daca e vida ar trebui sa arunce exceptie
		assert(false); //daca nu a aruncat exceptie, vrem sa avem un assert care da fail
	}
	catch (int e) {
		assert(true);
	}
}

void testAdauga() {
	Coada c;
	for (int i = 0; i < 10; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -10; i < 20; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -100; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);

	for (int i = 10000; i > -10000; i--) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	assert(c.element() != -9999);
	assert(c.element() == 0);

	assert(c.sterge() == 0);
	assert(c.element() == 1);
}

void testSterge() {
	Coada c;
	for (int i = 0; i < 10; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -10; i < 20; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);
	for (int i = -100; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.vida() == false);

	for (int i = 10000; i > -10000; i--) {
		c.adauga(i);
	}
	assert(c.vida() == false);

	// acum in aceeasi ordine ar trebui sa fie si sterse
	for (int i = 0; i < 10; i++) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == false);
	for (int i = -10; i < 20; i++) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == false);
	for (int i = -100; i < 100; i++) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == false);

	for (int i = 10000; i > -10000; i--) {
		assert(c.sterge() == i);
	}
	assert(c.vida() == true);
}

void testQuantity() {//scopul e sa adaugam multe date 
	Coada c;
	for (int i = 1; i <= 10; i++) {
		for (int j = 30000; j >= -3000; j--) {
			c.adauga(i + j);
		}
	}

	for (int i = 1; i <= 10; i++) {
		for (int j = 30000; j >= -3000; j--) {
			assert(c.sterge() == i + j);
		}
	}
}

void testAllExtins() {
	testCreeaza();
	testAdauga();
	testSterge();
	testQuantity();
}

int main()
{
	/*
	Coada c;
	assert(c.vida() == true);
	c.adauga(5);
	c.adauga(1);
	c.adauga(10);
	assert(c.vida() == false);
	assert(c.element() == 5);
	assert(c.sterge() == 5);
	assert(c.element() == 1);
	assert(c.sterge() == 1);
	assert(c.element() == 10);
	assert(c.sterge() == 10);
	assert(c.vida() == true);
	*/
	Coada c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(7);
	c.sterge();
	c.sterge();
	c.adauga(8);
	c.adauga(9);
	c.adauga(10);
	c.adauga(11);
	c.adauga(12);
	testAllExtins();
}