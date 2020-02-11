#pragma once
#include <vector>
#include <string>
#include "Echipa.h"

using std::vector;
using std::string;

class Repo
{
private:
	vector < Echipa > list;
	string filename;
	void loadFromFile();
public:
	Repo(string _file) : filename{ _file } {};
	vector < Echipa >& getAll(){
		//desc: functie ce returneaza ce e in repo
		loadFromFile();
		return list;
	}
	~Repo() {};
};

