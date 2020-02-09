#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct nod {
	int info;
	nod* left;
	nod* right;
};

nod* arbore(int pre[], int in[], int stPreordine, int drPreordine, int stInordine, int drInordine) {
	auto node = new nod;
	int pozRadacinaSubarbore = stPreordine;

	node->info = pre[pozRadacinaSubarbore];
	node->left = nullptr;
	node->right = nullptr;

	int steps = 0;
	int index = stInordine;
	while (index <= drInordine && in[index] != pre[pozRadacinaSubarbore])
		index++, steps++;

	if (index != stInordine) {
		cout << "STANGA ";
		cout << stPreordine + 1 << " " << stPreordine + steps << " " << stInordine << " " << stInordine+steps-1 << "\n";
		node->left = arbore(pre, in, stPreordine+1, stPreordine+steps, stInordine, index-1);
	}

	if (index != drInordine) {
		cout << "DREAPTA";
		cout << stPreordine + steps + 1 << " " << drPreordine << " " << steps + 2 << " " << drInordine << "\n";
		node->right = arbore(pre, in, stPreordine+steps+1, drPreordine, index + 1, drInordine);
	}

	return node;
}

int main()
{
	int pre[10] = { 0,1,2,8,4,7,9 };
	int in[10] = { 0,8,2,1,7,9,4 };

	auto rad = arbore(pre, in, 1, 6, 1, 6);


	queue < pair < nod*, string > > q;
	q.push({ rad, "RADACINA" });
	while (!q.empty()) {
		auto node = q.front().first;
		cout << node->info << " " << q.front().second << "\n";
		q.pop();
		if (node->left != nullptr)
			q.push({ node->left, "STANG" });
		if (node->right != nullptr) {
			q.push({ node->right, "DREPT" });
		}
	}

	return 0;
 }