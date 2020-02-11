#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

class Task
{
private:
	int id;
	string desc;
	vector < string > progrs;
	string stare;
public:
	Task(int id, string desc, vector < string > progrs, string stare) : id{ id }, desc{ desc }, progrs{ progrs }, stare{ stare } {};
	int getId() const {
		return id;
	}
	void setState(string new_state){
		stare = new_state;
	}
	string getDesc() const {
		return desc;
	}
	vector<string> getProgrs() const{
		return progrs;
	}
	string getStare() const {
		return stare;
	}
	bool operator==(const Task& t) {
		return (t.getId() == id);
	}
	~Task() {};
};

