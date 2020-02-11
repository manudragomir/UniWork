#include "Teste.h"
#include "Task.h"
#include "Repo.h"
#include "Valid.h"
#include <assert.h>
#include "Ctrl.h"
#include <fstream>

using std::ofstream;

void testTask() {
	Task t{ 10, "Epsilon", vector<string>{"A", "B", "C"}, "open" };
	assert(t.getId() == 10);
	assert(t.getDesc() == "Epsilon");
	assert(t.getStare() == "open");
	assert(t.getProgrs().size() == 3);
	Task t1{ 10, "Epsilon", vector<string>{"A", "B", "C"}, "open" };
	assert(t1 == t);
	t.setState("closed");
	assert(t.getStare() == "closed");
}

void testRepo() {
	Repo re{ "test.in" };
	assert(re.getAllTasks().size() == 10);
}

void testCtrl() {
	Repo re{ "test.in" };
	Valid vl;
	Ctrl ctrl{ re,vl };
	assert(ctrl.getAll().size() == 10);

	auto list = ctrl.filter("Progr3");
	assert(list.size() == 4);

	auto list1 = ctrl.filter("P");
	assert(list1.size() == 10);

	auto list2 = ctrl.getStare("open");
	assert(list2.size() == 3);

	auto id = list2.at(0).getId();
	ctrl.changeState(id, "closed");
	list2 = ctrl.getStare("open");
	assert(list2.size() == 2);
	
	ctrl.changeState(id, "open");

	ofstream fout("testadd.in");
	Repo re1{ "testadd.in" };
	Ctrl ctrl2{ re1, vl };

	try {
		ctrl2.add(1, "1", "open", vector < string>{"A", "B"});
		assert(true);
	}
	catch (MyException& ex) {
		assert(false);
	}

	try {
		ctrl2.add(2, "", "Closed", vector < string>{"A","B", "C", "D", "E"});
		assert(false);
	}
	catch (MyException& ex) {
		assert(ex.getMesaj().size() > 0);
	}

}

void Teste::testAllExtins()
{
	testTask();
	testRepo();
	testCtrl();
}
