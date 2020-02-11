#include "GRASP.h"

string GRASP::getMaxAtac()
{
	//determina echipa cu cel mai mare atac si retunreaza numele ei
	auto list = re.getAll();
	int max_atac = 0;
	string name;
	for (auto equipe : list) {
		if (equipe.getAtac() > max_atac) {
			max_atac = equipe.getAtac();
			name = equipe.getNume();
		}
	}
	return name;
}

string GRASP::getMaxMij()
{
	//determina echipa cu cel mai bun mijloc si retunreaza numele ei
	auto list = re.getAll();
	int max_mij = 0;
	string name;
	for (auto equipe : list) {
		if (equipe.getMij() > max_mij) {
			max_mij = equipe.getMij();
			name = equipe.getNume();
		}
	}
	return name;
}

string GRASP::getMaxAp()
{
	//determina echipa cu cea mai buna aparare si returneaza numele ei
	auto list = re.getAll();
	int max_ap = 0;
	string name;
	for (auto equipe : list) {
		if (equipe.getAp() > max_ap) {
			max_ap = equipe.getAp();
			name = equipe.getNume();
		}
	}
	return name;
}

vector < string > GRASP::rezolvaCampionat() {
	/*
	desc: primeste 8 echipe si face un campionat
	return: lista cu echipe si scorurile din acel campionat
	*/
	vector < string > solving;
	auto listSpania = this->getSpania();
	auto listAnglia = this->getAnglia();

	std::srand(unsigned(std::time(0)));
	std::random_shuffle(listAnglia.begin(), listAnglia.end());
	std::random_shuffle(listSpania.begin(), listSpania.end());

	Echipa winner[4];
	for (int i = 0; i < 4; i++) {
		auto scor = solveMeci(listAnglia[i], listSpania[i]);
		solving.push_back(listAnglia[i].getNume());
		if (scor.first >= scor.second)
			winner[i] = listAnglia[i];
		else
			winner[i] = listSpania[i];

		solving.push_back(std::to_string(scor.first));
		solving.push_back(std::to_string(scor.second));
		solving.push_back(listSpania[i].getNume());
	}

	Echipa ewinner[2];
	for (int i = 0; i < 2; i++) {
		auto scoru = solveMeci(winner[i], winner[i + 2]);
		solving.push_back(winner[i].getNume());
		if (scoru.first >= scoru.second)
			ewinner[i] = winner[i];
		else
			ewinner[i] = winner[i + 2];

		solving.push_back(std::to_string(scoru.first));
		solving.push_back(std::to_string(scoru.second));
		solving.push_back(winner[i + 2].getNume());

	}

	auto scorel = solveMeci(ewinner[0], ewinner[1]);

	Echipa zaWinner;
	if (scorel.first >= scorel.second)
		zaWinner = ewinner[0];
	else
		zaWinner = ewinner[1];

	solving.push_back(ewinner[0].getNume());
	solving.push_back(std::to_string(scorel.first));
	solving.push_back(std::to_string(scorel.second));
	solving.push_back(ewinner[1].getNume());

	solving.push_back(zaWinner.getNume());

	return solving;
}
