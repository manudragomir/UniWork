#pragma once
#include "Disciplina.h"
#include <vector>
#include <algorithm>
#include <fstream>

using std::vector;
using std::ofstream;

class Contract
{
private:
	vector < Disciplina > v;
public:
	Contract() = default;
	void goleste() {
		v.clear();
	}

	void sterge(const Disciplina& d) {
		v.erase(std::remove(v.begin(), v.end(), d), v.end());
	}
	
	void add(const Disciplina& d) {
		if(std::find(v.begin(), v.end(), d) == v.end())
			v.push_back(d);
	}

	vector<Disciplina>& get() {
		return this->v;
	}

	void store(string file){
		ofstream fout(file);
		for (auto it : v)
		{
			fout << it << "\n";
		}

		fout.close();
	}

	~Contract() = default;
};
