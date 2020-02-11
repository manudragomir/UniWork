#pragma once

template <typename TElem>
class IteratorLI;
//typedef int TElem;

template <typename TElem>
struct nod
{
	TElem info;
	nod* next;
};

template <typename TElem>
class vector
{

private:
	nod<TElem>* creeazaNod(TElem e)
	{
		nod<TElem>* node = new nod<TElem>;
		node->info = e;
		node->next = nullptr;
		return node;
	}

	nod<TElem>* prim;
	nod<TElem>* ultim;
	int dim;

public:

	vector() : prim{ nullptr }, dim{ 0 }, ultim{ nullptr } {}
	vector(int elems);
	vector(const vector<TElem>& l);
	void push_back(TElem);

	int size() const {
		return this->dim;
	}

	bool empty() const {
		return (this->dim == 0);
	}

	void erase(int);
	TElem& operator[](int index) const;
	vector<TElem>& operator=(const vector<TElem>&);

	friend class IteratorLI<TElem>;
	IteratorLI<TElem> begin() const;
	IteratorLI<TElem> end() const;

	~vector();
};


template <typename TElem>
vector<TElem>::vector(int elems)
{
	this->prim = nullptr;
	this->dim = 0;
	this->ultim = nullptr;

	for (int i = 0; i < elems; i++)
	{
		this->push_back(0);
	}
}

template <typename TElem>
vector<TElem>::vector(const vector& l)
{
	this->prim = nullptr;
	this->dim = 0;
	this->ultim = nullptr;

	for (int i = 0; i < l.size(); i++)
	{
		auto el = l[i];
		this->push_back(el);
	}
}

template <typename TElem>
void vector<TElem>::erase(int poz)
{
	int index = 0;
	nod<TElem>* prev = nullptr;
	nod<TElem>* curr = this->prim;
	while (index != poz)
	{
		prev = curr;
		curr = curr->next;
		index++;
	}

	if (index == 0)
	{
		this->prim = this->prim->next;
		delete curr;
		this->dim--;
		return;
	}

	if (curr == this->ultim)
	{
		this->ultim = prev;
		delete curr;
		this->dim--;
		return;
	}

	prev->next = curr->next;
	delete curr;
	this->dim--;


}

template <typename TElem>
void vector<TElem>::push_back(TElem e)
{
	if (this->prim == nullptr)
	{
		nod<TElem>* node = creeazaNod(e);
		this->prim = node;
		this->ultim = this->prim;
		this->dim++;
		return;
	}

	nod<TElem>* node = creeazaNod(e);
	this->ultim->next = node;
	this->ultim = node;
	this->dim++;
}

template <typename TElem>
TElem& vector<TElem>::operator[](int index) const
{
	nod<TElem>* current = this->prim;
	int i = 0;
	while (i < index)
	{
		current = current->next;
		i++;
	}

	return current->info;
}

template <typename TElem>
vector<TElem>& vector<TElem>::operator=(const vector<TElem>& l2)
{
	nod<TElem>* current = this->prim;
	while (current)
	{
		nod<TElem>* desters = current;
		current = current->next;
		delete desters;
	}

	for (int i = 0; i < l2.size(); i++)
	{
		auto el = l2[i];
		this->push_back(el);
	}
	return *this;
}

template <typename TElem>
vector<TElem>::~vector()
{
	nod<TElem>* current = this->prim;
	while (current)
	{
		nod<TElem>* desters = current;
		current = current->next;
		delete desters;
	}
}

template <typename TElem>
class IteratorLI {
private:
	const vector<TElem>& c;
	int poz;
public:
	IteratorLI(const vector<TElem>& l) : c{ l }, poz{ 0 } {};
	IteratorLI(const vector<TElem>& l, int poz) :c{ l }, poz{ poz }{};

	bool valid()const;
	TElem& element() const;
	void next();
	TElem& operator*();
	IteratorLI& operator++();
	bool operator==(const IteratorLI& ot);
	bool operator!=(const IteratorLI& ot);
};


template <typename TElem>
bool IteratorLI<TElem>::valid() const
{
	return poz < c.size();
}

template <typename TElem>
TElem& IteratorLI<TElem>::element() const
{
	return this->c[poz];
}

template <typename TElem>
inline void IteratorLI<TElem>::next()
{
	poz++;
}

template <typename TElem>
inline TElem & IteratorLI<TElem>::operator*()
{
	return element();
	// TODO: insert return statement here
}

template <typename TElem>
inline IteratorLI<TElem> & IteratorLI<TElem>::operator++()
{
	next();
	return *this;
	// TODO: insert return statement here
}

template <typename TElem>
bool IteratorLI<TElem>::operator==(const IteratorLI<TElem>& ot) {
	return poz == ot.poz;
}

template <typename TElem>
bool IteratorLI<TElem>::operator!=(const IteratorLI<TElem>& ot) {
	return !(*this == ot);
}

template <typename TElem>
IteratorLI<TElem> vector<TElem>::begin() const
{
	return IteratorLI<TElem>(*this);
}

template <typename TElem>
IteratorLI<TElem> vector<TElem>::end() const
{
	return IteratorLI<TElem>(*this, this->size());
}