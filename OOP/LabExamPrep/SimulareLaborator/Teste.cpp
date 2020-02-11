#include "Teste.h"
#include "Repo.h"
#include "GRASP.h"
#include <assert.h>
#include "Echipa.h"
#include <sstream>

using std::stringstream;

void Teste::testAllExtins()
{
	testEchipa();
	testRepo();
	testServ();
}

void Teste::testRepo()
{
	Repo re{ "test_input.txt" };
	assert(re.getAll().size() == 8);
}

void Teste::testServ()
{
	Repo re{ "test_input.txt" };
	GRASP serv{ re };
	assert(serv.getAllRepo().size() == 8);

	assert(serv.getMaxAp() == "Valencia");
	assert(serv.getMaxAtac() == "Real_Madrid");
	assert(serv.getMaxMij() == "Liverpool");

	auto list = re.getAll();
	assert(serv.solveMeci(list[0], list[1]).first > serv.solveMeci(list[0], list[1]).second);
	assert(serv.getAnglia().size() == 4);
	assert(serv.getSpania().size() == 4);
	auto lista = serv.rezolvaCampionat();
	assert(lista[lista.size() - 1] == "Manchester_United");
}

void Teste::testEchipa()
{
	stringstream out;
	out.write("Real_Madrid 1 0.1 0.1 Spania", 28);
	assert(out.str() == "Real_Madrid 1 0.1 0.1 Spania");
	Echipa ec;
	out >> ec;
	assert(ec.getNume() == "Real_Madrid");
	assert(ec.getAp() == 0.1);
	assert(ec.getAtac() == 1);
	assert(ec.getMij() == 0.1);
	assert(ec.getTara() == "Spania");
}
