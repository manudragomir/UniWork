#include "Repo.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

void Repo::loadFromFile()
{
	v.clear();
	ifstream f(filename);
	int id;
	string desc;
	vector<string>progr;
	string stare;
	while (f >> id) {
		progr.clear();
		f >> desc;
		f >> stare;
		int nr;
		f >> nr;
		for (int i = 0; i < nr; i++) {
			string p;
			f >> p;
			progr.push_back(p);
		}
		v.push_back(Task{ id,desc,progr,stare });
	}
}

void Repo::storeToFile()
{
	ofstream out(filename);
	for (const auto& el : v) {
		out << el.getId() << " " << el.getDesc() << " " << el.getStare() << " " << el.getProgrs().size() << " ";
		for (const auto& pr : el.getProgrs()) {
			out << pr << " ";
		}
		out << "\n";
	}
}
