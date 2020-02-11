#pragma once
#include<string>

using std::string;

class Disciplina
{
private:
	string denumire;
	int ore{ 0 };
	string tip;
	string cadru_didactic;

public:
	Disciplina() = default;
	Disciplina(string, int, string, string);
	const string& get_denumire() const;
	int get_ore() const;
	const string& get_tip() const;
	const string& get_cadru_didactic() const;
	string toString() const;
	bool egal(const Disciplina& ot) const;
	Disciplina& operator=(const Disciplina& ot);

	~Disciplina();
};

