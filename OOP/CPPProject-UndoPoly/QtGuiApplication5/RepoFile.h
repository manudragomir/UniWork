#pragma once
#include "Repository.h"

class RepoFile: public Repository
{
private:
	string filename;
	void loadFromFile();
	void storeToFile();
	
public:
	
	RepoFile(string _filename) : filename{ _filename } { this->loadFromFile(); };
	void storeRepo(const Disciplina& d) override {
		Repository::storeRepo(d);
		storeToFile();
	}
	void deleteRepo(const Disciplina& d) override {
		Repository::deleteRepo(d);
		storeToFile();
	}
	void updateRepo(const Disciplina& d) override {
		Repository::updateRepo(d);
		storeToFile();
	}

	~RepoFile() {};
	
};

