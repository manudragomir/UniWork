#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"

using std::vector;

class Observable
{
private:
	vector < Observer*> observers;
public:
	Observable() {};
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	/*
	void remObserver(Observer* obs) {
		for (auto it : observers) {
			if (it == obs) {
				observers.erase(it);
			}
		}
	}
	*/
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
	~Observable() {};
};

