#pragma once
#include <string>

using std::string;

class DisciplinaExc
{
private:
	string msj;
public:
	DisciplinaExc(string _msj) : msj{ _msj } {

	}

	const string& toString() {
		return this->msj;
	}
};

class RepoExc
{
private:
	string msj;
public:
	RepoExc(string _msj) : msj{ _msj } {

	}

	const string& toString() {
		return this->msj;
	}
};
