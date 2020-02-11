#pragma once
#include <vector>
#include "Observer.h"

using std::vector;

class Observable
{
	vector < Observer* > obs;
public:
	Observable() {};
	void addObserver(Observer* o) {
		obs.push_back(o);
	}
	void notify() {
		for (const auto& o : obs) {
			o->update();
		}
	}
	~Observable() {};
};

