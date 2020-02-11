#pragma once
#include "Repo.h"
#include "Valid.h"
#include <algorithm>
#include <vector>
#include "Observable.h"


using std::vector;

class Ctrl : public Observable
{
	Repo& re;
	Valid& vl;
public:
	Ctrl(Repo& re, Valid& vl) : re{ re }, vl{ vl } {};
	void add(int id, string desc, string stare, vector<string>progr) {
		Task t{ id,desc,progr,stare };
		vl.valideaza(t);
		re.addTask(t);
		notify();
	}
	void changeState(int id, string new_state) {
		re.updateTask(id, new_state);
		notify();
	}
	const vector <Task>& getAll() const{
		return re.getAllTasks();
	}
	const vector <Task> getStare(string stare) const {
		vector<Task> lst;
		auto lista = re.getAllTasks();
		std::copy_if(lista.begin(), lista.end(), std::back_inserter(lst), [stare](const Task& t) {return (t.getStare() == stare); });
		return lst;
	}
	const vector <Task> filter(string s) const {
		vector < Task > p;
		auto list = re.getAllTasks();
		for (const auto& el : list) {
			auto listProg = el.getProgrs();
			bool ok{ false };
			for (const auto& pr : listProg) {
				if (pr.find(s) >= 0 && pr.find(s) < pr.size()) {
					ok = true;
				}

			}
			if (ok == true) {
				p.push_back(el);
			}
		}
		return p;
	}
	~Ctrl() {};
};

