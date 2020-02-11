#include "Disciplina.h"
#include "Repository.h"
#include "RepoFile.h"
#include "GRASPController.h"
#include "Contract.h"
#include "Validator.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;

void TestDisciplina()
{
	//test creare disciplina
	Disciplina d1{ "OOP",6,"T1","Istvan Czibula" };
	assert(d1.get_cadru_didactic() == "Istvan Czibula");
	assert(d1.get_tip() == "T1");
	assert(d1.get_ore() == 6);
	assert(d1.get_denumire() == "OOP");
	assert(d1.toString() == "OOP 6 T1 Istvan Czibula");

	std::ostringstream os;
	os << d1;
	assert(os.str() == "OOP 6 T1 Istvan Czibula");
	
	Disciplina d2{ "OOP",10,"T2","Gabi Mircea" };
	assert(d1 == d2);
}

void TestRepo()
{
	//test adauga in repo + getall
	Disciplina d1{ "OOP",6,"T1","Istvan Czibula" };
	Disciplina d2{ "SDA",10,"T2","Gabi Czibula" };
	Repository r;
	r.storeRepo(d1);
	r.storeRepo(d2);
	r.getElement(Disciplina{ "SO", 10, "T1", "Istvan" });

	auto lista = r.getAllRepo();
	assert(lista.size() == 2);
	Disciplina d3{ "OS",10,"T3","Boian Rares" };
	try{
		r.deleteRepo(d3);
		assert(false);
	}
	catch(RepoExc&){
		assert(true);

	}

	try {
		r.storeRepo(d1);
		assert(false);
	}
	catch (RepoExc&){
		assert(true);
	}

	try {
		r.updateRepo(d3);
		assert(false);
	}
	catch (RepoExc& re)
	{
		std::ostringstream os;
		os << re;
		assert(os.str() == "Nu se poate updata un element inexistent\n");
		assert(true);
	}
}

void TestServ()
{
	//test add service
	Repository r;
	Validator v;
	Contract c;
	GRASPController serv{ r, v, c};
	serv.add("OOP", 6, "T1", "Istvan");
	assert(serv.getAllElements().size() == 1);

	//test delete service
	serv.deletee("OOP");
	assert(serv.getAllElements().size() == 0);

	//test search both cases
	assert(serv.search("OOP") == false);
	serv.add("OOP", 6, "T1", "Istvan");
	assert(serv.search("OOP") == true);

	//test update service
	serv.modify("OOP", 2, "T2", "Czibula");
	assert(serv.getAllElements().at(0).get_cadru_didactic() == "Czibula");

	//test filters
	serv.add("SDA", 3, "T3", "Czibula");
	serv.add("SO", 4, "T4", "Boian");

	vector < Disciplina > list1 = serv.filterCd("Czibula");
	assert(list1.size() == 2);

	vector <Disciplina > list2 = serv.filterOre(4);
	assert(list2.size() == 1);

	//test sort

	//case1
	vector <Disciplina> list = serv.sorting(1);
	assert(list.at(0).toString() == "OOP 2 T2 Czibula");
	assert(list.at(1).toString() == "SDA 3 T3 Czibula");
	assert(list.at(2).toString() == "SO 4 T4 Boian");

	//case2
	vector < Disciplina> list3 = serv.sorting(2);
	assert(list3.at(0).toString() == "OOP 2 T2 Czibula");
	assert(list3.at(1).toString() == "SDA 3 T3 Czibula");
	assert(list3.at(2).toString() == "SO 4 T4 Boian");

	//case3
	vector < Disciplina > list4 = serv.sorting(3);
	assert(list4.at(1).toString() == "OOP 2 T2 Czibula");
	assert(list4.at(2).toString() == "SDA 3 T3 Czibula");
	assert(list4.at(0).toString() == "SO 4 T4 Boian");
}

void TestValidator()
{
	Validator val;
	Disciplina d1{ "OOP",6,"T1","Istvan Czibula" };
	try{
		val.validate(d1);
		assert(true);
	}
	catch (DisciplinaExc& ){
		assert(false);
	}

	Disciplina d2{ "",-2,"","" };

	try {
		val.validate(d2);
		assert(false);
	}
	catch (DisciplinaExc& e) {
		std::ostringstream os;
		os << e;
		assert(os.str() == "Denumirea nu poate fi vida\nNr de ore nu poate fi nenatural\nTipul nu poate fi vid\nCD-ul nu poate fi vid\n");
		assert(true);	
		//cout << e.toString();
	}

}

void TestUndo()
{
	Repository r;
	Validator v;
	Contract c;
	GRASPController serv{ r, v, c };

	//test undo for add
	serv.add("OOP", 6, "T1", "Istvan");
	assert(serv.getAllElements().size() == 1);
	serv.undo();
	assert(serv.getAllElements().size() == 0);

	try {
		serv.undo();
		assert(false);
	}
	catch(DisciplinaExc& ){
		assert(true);
	}

	//test undo for delete
	serv.add("OOP", 6, "T1", "Istvan");
	assert(serv.getAllElements().size() == 1);
	serv.deletee("OOP");
	assert(serv.getAllElements().size() == 0);
	serv.undo();
	assert(serv.getAllElements().size() == 1);
	
	serv.modify("OOP", 10, "T2", "Czibula");
	assert(serv.getAllElements().at(0).get_cadru_didactic() == "Czibula");
	serv.undo();
	assert(serv.getAllElements().at(0).get_cadru_didactic() == "Istvan");
}

void TestRepoFile()
{
	std::ofstream("test.txt");
	RepoFile rep{ "test.txt" };
	rep.storeRepo(Disciplina("oop", 10, "t1", "istvan"));
	assert(rep.getAllRepo().size() == 1);
	rep.updateRepo(Disciplina("oop", 15, "t2", "czibi"));
	assert(rep.getAllRepo().at(0).get_cadru_didactic() == "czibi");
	rep.deleteRepo(Disciplina("oop",15,"t2", "czibi"));
	assert(rep.getAllRepo().size() == 0);
}

void TestContract()
{
	Repository r;
	Validator v;
	Contract c;
	GRASPController serv{ r, v, c };
	serv.add("OOP", 10, "S2", "Istvan");
	serv.add("FP", 10, "S1", "Istvan");
	serv.add("SO", 5, "S2", "Boian");
	serv.add("SD", 10, "S2", "Serban");
	serv.add("SDA", 10, "S2", "Diana");
	serv.add("ALGEBRA", 7, "S1", "Mo2");
	int x = serv.addContract("OOP");
	assert(x == 1);
	int len = serv.getContract().size();
	assert(len == 1);

	x = serv.golContract();
	assert(x == 0);	

	int nr = serv.genContract(3);
	std::ofstream fout("testCntr.txt");
	serv.saveContract("testCntr.txt");
	std::ifstream fin("testCntr.txt");
	Disciplina dis;
	int cnt = 0;
	while (fin >> dis)
		cnt++;
	assert(cnt == nr);

}

void TestAllExtins()
{
	TestValidator();
	TestDisciplina();
	TestRepo();
	TestServ();
	TestUndo();
	TestRepoFile();
	TestContract();
	cout << "Toate testele merg!\n";
}