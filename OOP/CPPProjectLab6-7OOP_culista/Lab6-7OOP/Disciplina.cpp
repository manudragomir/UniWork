#include "Disciplina.h"

/*
Disciplina::Disciplina()
{
}
*/

Disciplina::Disciplina(string den, int ore, string tip, string cd): denumire{den}, ore{ore}, tip{tip}, cadru_didactic{cd}{
}

const string& Disciplina::get_denumire() const
{
	return this->denumire;
}

int Disciplina::get_ore() const
{
	return this->ore;
}

const string& Disciplina::get_tip() const
{
	return this->tip;
}

const string& Disciplina::get_cadru_didactic() const
{
	return this->cadru_didactic;
}

string Disciplina::toString() const
{
	return this->denumire + " " + std::to_string(this->ore) + " " + this->tip + " " + this->cadru_didactic;
}

bool Disciplina::egal(const Disciplina& ot) const
{
	return (this->denumire == ot.get_denumire());
}

Disciplina & Disciplina::operator=(const Disciplina & ot)
{
	this->ore = ot.get_ore();
	this->denumire = ot.get_denumire();
	this->cadru_didactic = ot.get_cadru_didactic();
	this->tip = ot.get_tip();
	return *this;
	// TODO: insert return statement here
}


Disciplina::~Disciplina()
{
}
