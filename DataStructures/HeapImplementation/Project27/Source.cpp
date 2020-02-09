#include <iostream>

using namespace std;

template <typename T>
class Heap
{
	T a[100];
	int n;

	bool(*f)(T, T);
	void URCA(int poz) {
		auto pozParinte = poz / 2;
		auto pozCurenta = poz;
		while (pozParinte >= 1 && f(a[pozCurenta], a[pozParinte])) {
			auto aux = a[pozCurenta];
			a[pozCurenta] = a[pozParinte];
			a[pozParinte] = aux;
			pozCurenta = pozParinte;
			pozParinte = pozCurenta / 2;
		}
	}
	void COBOARA(int poz) {
		auto pozCurenta = poz;
		auto pozFiu = poz * 2;
		while (pozFiu <= n) {
			if (pozFiu + 1 <= n && f(a[pozFiu + 1], a[pozFiu])) {
				pozFiu++;
			}
			if (f(a[pozFiu], a[pozCurenta])) {
				auto aux = a[pozCurenta];
				a[pozCurenta] = a[pozFiu];
				a[pozFiu] = aux;
			}
			else {
				pozFiu = n + 1;
			}
		}
	}
public:
	Heap<T>(bool(*functie)(T, T)) {
		f = functie;
	};
	void add(T elem) {
		n++;
		a[n] = elem;
		URCA(n);
	}
	T sterge() {
		auto el = a[1];
		a[1] = a[n];
		n--;
		COBOARA(1);
		return el;
	}
	~Heap<T>() {};
};

bool maiMic(int a, int b) {
	return a < b;
}

int main()
{
	Heap<int> heap(maiMic);
	heap.add(5);
	heap.add(3);
	heap.add(4);
	heap.add(1);
	heap.add(2);
	cout << heap.sterge();
	cout << heap.sterge();
	cout << heap.sterge();
	cout << heap.sterge();
	cout << heap.sterge();
	
	return 0;
}