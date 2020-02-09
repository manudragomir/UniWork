#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>



IteratorMDO::IteratorMDO(const MDO& _c) : c{ _c }  {
	stack < Node* > st;
	Node* p = c.root;
	while (!st.empty() || p != nullptr) {
		while (p != nullptr) {
			st.push(p);
			p = p->left;
		}
		p = st.top();
		st.pop();
		iterate.push_back(p);
		p = p->right;
	}
}

void IteratorMDO::prim()
{
	indexCheie = 0;
	indexValoare = 0;
}

void IteratorMDO::urmator()
{
	indexValoare++;
	if (indexValoare == (iterate.at(indexCheie))->values.size()) {
		indexCheie++;
		indexValoare = 0;
	}
}

void IteratorMDO::anterior()
{
	indexValoare--;
	if (indexValoare < 0) {
		if (indexCheie > 0){
			indexCheie--;
			indexValoare = (iterate.at(indexCheie)->values.size() - 1);
		}
		else {
			invalid = false;
		}
	}
}


bool IteratorMDO::valid() const
{
	return ((indexCheie < iterate.size()) && invalid);
}

TElem IteratorMDO::element() const
{
	if (valid() == false) {
		throw -1;
	}
	return { (iterate.at(indexCheie))->info, (iterate.at(indexCheie))->values.at(indexValoare) };
}

