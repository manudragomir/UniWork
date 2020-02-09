#include <iostream>

using namespace std;

class SegmentTree {
private:
	int* tree;
	int N;
	void RecursiveInsertion(int left, int right, int index, int value, int pos) {
		if (left == right) {
			tree[pos] = value;
			return;
		}
		
		int mij = (left + right) / 2;
		if (index <= mij) {
			RecursiveInsertion(left, mij, index, value, 2*(pos+1)-1);
		}
		else {
			RecursiveInsertion(mij+1, right, index, value, 2*(pos+1));
		}

		tree[pos] = tree[2 * (pos + 1) - 1] + tree[2 * (pos + 1)];
	}
	void create(int left, int right, int v[], int pos) {
		if (left == right) {
			tree[pos] = v[left];
			return;
		}

		int mij = (left + right) / 2;
		create(left, mij, v, 2 * (pos + 1) - 1);
		create(mij + 1, right, v, 2 * (pos + 1));

		tree[pos] = tree[2 * (pos + 1) - 1] + tree[2 * (pos + 1)];
	}
	void getSum(int left, int right, int a, int b, int& sum, int pos) {
		if (a <= left && right <= b) {
			sum += tree[pos];
			return;
		}

		int mij = (left + right) / 2;
		if (a <= mij) {
			getSum(left, mij, a, b, sum, 2 * (pos + 1) - 1);
		}
		if (b > mij) {
			getSum(mij + 1, right, a, b, sum, 2 * (pos + 1));
		}

	}
public:
	SegmentTree(int v[], int _N) {
		N = _N;
		tree = new int[4*N + 1];
		for (int i = 0; i < 4*N+1; i++) {
			tree[i] = 0;
		}
		create(0, N - 1, v, 0);
	}
	void insert(int index, int value) {
		RecursiveInsertion(0, N-1, index, value, 0);
	}
	int sum(int left, int right) {
		int sum = 0;
		getSum(0, N - 1, left, right, sum, 0);
		return sum;
	}
	~SegmentTree() {
		delete[] tree;
	}

	void print() {
		for (int i = 0; i < 9; i++) {
			cout << tree[i] << " ";
		}
	}
};

int main() {
	int v[] = { 1,3,-2,8,-7 };
	SegmentTree t{ v, 5 };
	t.print();
	cout << "\n";
	cout << t.sum(1, 3);
	return 0;
}