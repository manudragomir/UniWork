#include "Disciplina.h"
#include "Repository.h"
#include "GRASPController.h"
#include "Validator.h"
#include <cassert>
#include <iostream>

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
	
	Disciplina d2{ "OOP",10,"T2","Gabi Mircea" };
	assert(d1.egal(d2) == true);
}

void TestRepo()
{
	//test adauga in repo + getall
	Disciplina d1{ "OOP",6,"T1","Istvan Czibula" };
	Disciplina d2{ "SDA",10,"T2","Gabi Czibula" };
	Repository r;
	r.storeRepo(d1);
	r.storeRepo(d2);

	auto lista = r.getAllRepo();
	assert(lista.size() == 2);
}

void TestServ()
{
	//test add service
	Repository r;
	Validator v;
	GRASPController serv{ r, v};
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
	assert(serv.getAllElements()[0].get_cadru_didactic() == "Czibula");

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
	assert(list[0].toString() == "OOP 2 T2 Czibula");
	assert(list[1].toString() == "SDA 3 T3 Czibula");
	assert(list[2].toString() == "SO 4 T4 Boian");

	//case2
	vector < Disciplina> list3 = serv.sorting(2);
	assert(list3[0].toString() == "OOP 2 T2 Czibula");
	assert(list3[1].toString() == "SDA 3 T3 Czibula");
	assert(list3[2].toString() == "SO 4 T4 Boian");

	//case3
	vector < Disciplina > list4 = serv.sorting(3);
	assert(list4[1].toString() == "OOP 2 T2 Czibula");
	assert(list4[2].toString() == "SDA 3 T3 Czibula");
	assert(list4[0].toString() == "SO 4 T4 Boian");
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
	catch (DisciplinaExc& ) {
		assert(true);
		//cout << e.toString();
	}

}

void TestAllExtins()
{
	TestValidator();
	TestDisciplina();
	TestRepo();
	TestServ();
	cout << "Toate testele merg!\n";
}