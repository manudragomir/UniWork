#pragma once
#include <vector>
#include "Valid.h"
#include "Task.h"

using std::vector;

class Repo
{
private:
	vector < Task > v;
	string filename;
	void loadFromFile();
	void storeToFile();
public:
	Repo(string filename) : filename{ filename } {};
	void addTask(const Task& t) {
		for (const auto& el : v) {
			if (t.getId() == el.getId()) {
				throw MyException("Id neunic");
			}
		}
		v.push_back(t);
		storeToFile();
	}
	void updateTask(int id, string new_state) {
		for (auto& el : v) {
			if (el.getId() == id) {
				el.setState(new_state);
			}
		}
		storeToFile();
	}
	const vector < Task >& getAllTasks(){
		loadFromFile();
		return v;
	}
	~Repo() {};
};

