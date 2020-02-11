#pragma once
#include <string>
#include <iostream>

using std::string;

class DisciplinaExc
{
private:
	string msj;
public:
	DisciplinaExc(string _msj) : msj{ _msj } {

	}

	friend std::ostream& operator<<(std::ostream& os, const DisciplinaExc& de)
	{
		os << de.msj;
		return os;
	}
};

class RepoExc
{
private:
	string msj;
public:
	RepoExc(string _msj) : msj{ _msj } {

	}

	friend std::ostream& operator<<(std::ostream& os, const RepoExc& re)
	{
		os << re.msj;
		return os;
	}
};
