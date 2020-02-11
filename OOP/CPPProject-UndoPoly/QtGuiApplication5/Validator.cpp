#include "Validator.h"



void Validator::validate(const Disciplina & d)
{
	string errors = "";
	if (d.get_denumire() == "")
		errors += "Denumirea nu poate fi vida\n";
	if (d.get_ore() <= 0)
		errors += "Nr de ore nu poate fi nenatural\n";
	if (d.get_tip() == "")
		errors += "Tipul nu poate fi vid\n";
	if (d.get_cadru_didactic() == "")
		errors += "CD-ul nu poate fi vid\n";
	
	if (errors.size() != 0)
		throw DisciplinaExc(errors);

}
