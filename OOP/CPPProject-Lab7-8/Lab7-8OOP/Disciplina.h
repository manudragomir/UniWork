#pragma once
#include<string>
#include<iostream>

using std::string;
using std::ostream;
using std::istream;

class Disciplina
{
private:
	string denumire;
	int ore{ 0 };
	string tip;
	string cadru_didactic;

public:
	Disciplina() : denumire{ "" }, ore{ 0 }, tip{ "" }, cadru_didactic{ "" } {};
	Disciplina(string, int, string, string);
	const string& get_denumire() const noexcept;
	int get_ore() const noexcept;
	const string& get_tip() const noexcept;
	const string& get_cadru_didactic() const noexcept;
	string toString() const;
	//bool egal(const Disciplina& ot) const;
	bool operator==(const Disciplina& ot) noexcept;
	Disciplina& operator=(const Disciplina& ot);
	friend ostream& operator<<(ostream& os, const Disciplina& d){
		os << d.get_denumire() << " " << d.get_ore() << " " << d.get_tip() << " "<< d.get_cadru_didactic();
		return os;
	}

	friend istream& operator>>(istream& is, Disciplina& d) {
		is >> d.denumire >> d.ore >> d.tip >> d.cadru_didactic;
		return is;
	}

	~Disciplina();
};

