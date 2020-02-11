#pragma once
#include "Task.h"
#include <string>
#include <exception>

using std::string;

class MyException
{
private:
	string mesaj;
public:
	MyException(string m) : mesaj{ m } {};
	string getMesaj() {
		return mesaj;
	}
};

class Valid
{
public:
	Valid() {};
	void valideaza(const Task& t1) {
		string errors = "";
		if (t1.getDesc().size() == 0)
			errors += "Descriere vida\n";
		if (t1.getProgrs().size() < 1 || t1.getProgrs().size() > 4) {
			errors += "Too much progrs\n";
		}
		if (t1.getStare() != "closed" && t1.getStare() != "open" && t1.getStare() != "inprogress") {
			errors += "Stare inexis\n";
		}

		if (errors.size() > 0)
			throw MyException(errors);
	}
	~Valid() {};
};



