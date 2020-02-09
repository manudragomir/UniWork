#include "MDO.h"
#include <algorithm>

Node* MDO::cauta_iterativ(Node* nod, TCheie c) const
{
	while (nod != nullptr && nod->info != c) {
		if (R(c, nod->info)) {
			nod = nod->left;
		}
		else {
			nod = nod->right;
		}
	}

	return nod;
}

Node* MDO::adauga_recursiv(Node* nod, TCheie c, TValoare v)
{
	if (nod == nullptr) {
		nod = new Node{ c };
		nod->values.push_back(v);
	}
	else {
		if (nod->info == c) {
			nod->values.push_back(v);
		}
		else if (R(c,nod->info)) {
			nod->left = adauga_recursiv(nod->left, c, v);
		}
		else {
			nod->right = adauga_recursiv(nod->right, c, v);
		}
	}

	return nod;
}

Node * MDO::sterge_recursiv(Node * nod, TCheie c, TValoare v, bool& sters)
{
	if (nod == nullptr) {
		return nullptr;
	}
	
	else {
		if (nod->info == c) {
			//suntem pe nodul ce trebuie sters
			auto iterator = std::find_if(nod->values.begin(), nod->values.end(), [v](const TValoare& iteratedValue) {
				return (iteratedValue == v);
			});

			if (iterator == nod->values.end()) {
				return nod;
			}

			else {
				sters = true;
				nod->values.erase(iterator);
				if (nod->values.size() != 0)
					return nod;
				else {
					if (nod->left != nullptr && nod->right != nullptr) {
						auto temp = minim(nod->right);
						nod->info = temp->info;
						nod->right = sterge_recursiv(nod->right, temp->info, v, sters);
						return nod;
					}
					else {
						auto temp = nod;
						Node* swp;
						if (nod->left == nullptr) {
							swp = nod->right;
						}
						else {
							swp = nod->left;
						}
						delete nod;
						return swp;
					}
				}
			}
		}

		if (R(c, nod->info)) {
			nod->left = sterge_recursiv(nod->left, c, v, sters);
			return nod;
		}

		else if (R(nod->info, c)) {
			nod->right = sterge_recursiv(nod->right, c, v, sters);
			return nod;
		}
	}
}

Node * MDO::minim(Node * nod)
{
	while (nod->left != nullptr) {
		nod = nod->left;
	}

	return nod;
}

MDO::MDO(Relatie r)
{
	size = 0;
	R = r;
	root = nullptr;
}

void MDO::adauga(TCheie c, TValoare v)
{
	root = adauga_recursiv(root, c, v);
	++size;
}

vector<TValoare> MDO::cauta(TCheie c) const
{
	auto nod = cauta_iterativ(root, c);
	if (nod == nullptr)
		return vector < TValoare>();
	return nod->values;
}

bool MDO::sterge(TCheie c, TValoare v)
{
	bool check{ false };
	root = sterge_recursiv(root, c, v, check);
	if (check == true) {
		--size;
	}
	return check;
}

int MDO::dim() const
{
	return size;
}

bool MDO::vid() const
{
	return (size == 0);
}

IteratorMDO MDO::iterator() const
{
	return IteratorMDO(*this);
}
