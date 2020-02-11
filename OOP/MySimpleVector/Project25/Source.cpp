#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Vector
{
	vector<T> lst;
public:
	Vector& add(T elem) {
		lst.push_back(elem);
		return *this;
	}
	T getValue() const{
		return lst.back();
	}
	T operator[](int value) {
		return lst.at(value);
	}
	Vector operator--(int) {
		auto asta = *this;
		lst.pop_back();
		return asta;
	}
	Vector& operator--(){
		lst.pop_back();
		return *this;
	}
	friend ostream& operator<<(ostream& os, const Vector& v) {
		os << v.getValue();
		return os;
	}

};

int main() {
	Vector<int> lst;
	lst.add(5).add(7).add(8);
	cout << lst--;
}