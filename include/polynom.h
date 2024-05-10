#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

double binpow(double a, int n) {
	double res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

template<typename First, typename Second> struct Pair {
	First First;
	Second Second;
	friend auto operator<(const Pair& a, const Pair& b)
	{
		return a.Second < b.Second;
	}
	friend auto operator<=(const Pair& a, const Pair& b)
	{
		return a.Second <= b.Second;
	}
	friend auto operator>=(const Pair& a, const Pair& b)
	{
		return a.Second >= b.Second;
	}
	friend auto operator>(const Pair& a, const Pair& b)
	{
		return a.Second > b.Second;
	}
	friend bool operator==(const Pair& a, const Pair& b)
	{
		if ((a.Second == b.Second) && (a.First == b.First))
			return(true);
		else
			return(false);
	}
	friend bool operator!=(const Pair& a, const Pair& b)
	{
		if ((a.Second == b.Second) && (a.First == b.First))
			return(false);
		else
			return(true);
	}
};

template<typename T> class AVL_tree {
	struct Node
	{
		T Duo; //Second = key, First = value
		Node* pL;
		Node* pR;
		Node* pP;
		int balance = 0;

		friend bool operator==(const Node& a, const Node& b)
		{
			if (a.Duo != b.Duo)
				return(false);
			if ((a.pL != nullptr) && (b.pL != nullptr)) {
				if (a.pL->Duo != b.pL->Duo)
					return(false);
			}
			else
				if (a.pL != b.pL)
					return(false);
			if ((a.pR != nullptr) && (b.pR != nullptr)) {
				if (a.pR->Duo != b.pR->Duo)
					return(false);
			}
			else
				if (a.pR != b.pR)
					return(false);
			if ((a.pP != nullptr) && (b.pP != nullptr)) {
				if (a.pP->Duo != b.pP->Duo)
					return(false);
			}
			else
				if (a.pP != b.pP)
					return(false);
			return(true);
		}
	};

	Node* pFirst;
	size_t sz;

	class AVL_tree_Iterator {
		friend class AVL_tree;
	public:
		typedef Node iterator_type;
		typedef input_iterator_tag iterator_category;
		typedef iterator_type iterator_value;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

	private:
		iterator_type* value;
		int left_block = 0;
		int right_block = 0;
	public:
		AVL_tree_Iterator(Node* p) : value(p), left_block(0), right_block(0) {}
		AVL_tree_Iterator(AVL_tree_Iterator& it) : value(it.value), left_block(it.left_block), right_block(it.right_block) {}
		AVL_tree_Iterator(const AVL_tree_Iterator& it) : value(it.value), left_block(it.left_block), right_block(it.right_block) {}
		typename AVL_tree_Iterator::reference operator*() {
			return(*value);
		}
		AVL_tree_Iterator& operator++() {
			while (true) {
				if (value->pL == nullptr)
					left_block = 1;
				if (value->pR == nullptr)
					right_block = 1;
				if (left_block != 1) {
					value = value->pL;
					return(*this);
				}
				if (right_block != 1) {
					value = value->pR;
					if (value->pL != nullptr)
						left_block = 0;
					return(*this);
				}
				if ((value->pP == nullptr) && (right_block == 1) && (left_block == 1)) {
					value = nullptr;
					return(*this);
				}
				if (((value->pP)->pL) == value)
					right_block = 0;
				value = value->pP;
			}
		}
		bool operator!=(AVL_tree_Iterator const& other) {
			return(value != other.value);
		}
		bool operator==(AVL_tree_Iterator const& other) {
			return(!(value != other.value));
		}
	};

private:

	int balancing(Node* iter) {
		if ((iter->balance == -2) && ((iter->pL)->balance < 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = (iter->pL);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = (iter->pL);
			}
			(iter->pP) = (iter->pL);
			(iter->pL) = ((iter->pL)->pR);
			if (iter->pL != nullptr) {
				(((iter->pL)->pP)->pP) = tmp;
				(((iter->pL)->pP)->pR) = iter;
				((iter->pL)->pP) = iter;
			}
			else {
				(iter->pP)->pP = tmp;
				(iter->pP)->pR = iter;
			}
			iter->balance = 0;
			iter->pP->balance = 0;
			return(1);
		}
		if ((iter->balance == -2) && ((iter->pL)->balance > 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = ((iter->pL)->pR);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = ((iter->pL)->pR);
			}
			(iter->pP) = ((iter->pL)->pR);
			(iter->pL) = (((iter->pL)->pR)->pR);
			if (iter->pL != nullptr)
				((iter->pL)->pP) = (iter);
			(iter->pP)->pR = iter;
			(((iter->pP)->pP)->pR) = ((iter->pP)->pL);
			((iter->pP)->pL) = ((iter->pP)->pP);
			(((iter->pP)->pP)->pP) = (iter->pP);
			if (((iter->pP)->pL)->pR != nullptr)
				((((iter->pP)->pL)->pR)->pP) = ((iter->pP)->pP);
			((iter->pP)->pP) = tmp;
			if ((iter->pP)->balance == -1) {
				iter->balance = 1;
				((iter->pP)->pL)->balance = 0;
				(iter->pP)->balance = 0;
			}
			else if ((iter->pP)->balance == 1) {
				iter->balance = 0;
				((iter->pP)->pL)->balance = 1;
				(iter->pP)->balance = 0;
			}
			else {
				iter->balance = 0;
				((iter->pP)->pL)->balance = 0;
				(iter->pP)->balance = 0;
			}
			return(1);
		}
		if ((iter->balance == 2) && ((iter->pR)->balance > 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = (iter->pR);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = (iter->pR);
			}
			(iter->pP) = (iter->pR);
			(iter->pR) = ((iter->pR)->pL);
			if (iter->pR != nullptr) {
				(((iter->pR)->pP)->pP) = tmp;
				(((iter->pR)->pP)->pL) = iter;
				((iter->pR)->pP) = iter;
			}
			else {
				(iter->pP)->pP = tmp;
				(iter->pP)->pL = iter;
			}
			iter->balance = 0;
			(iter->pP)->balance = 0;
			return(1);
		}
		if ((iter->balance == 2) && ((iter->pR)->balance < 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = ((iter->pR)->pL);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = ((iter->pR)->pL);
			}
			(iter->pP) = ((iter->pR)->pL);
			(iter->pR) = (((iter->pR)->pL)->pL);
			if (iter->pR != nullptr)
				((iter->pR)->pP) = (iter);
			(iter->pP)->pL = iter;
			(((iter->pP)->pP)->pL) = ((iter->pP)->pR);
			((iter->pP)->pR) = ((iter->pP)->pP);
			(((iter->pP)->pP)->pP) = (iter->pP);
			if (((iter->pP)->pR)->pL != nullptr)
				((((iter->pP)->pR)->pL)->pP) = ((iter->pP)->pP);
			((iter->pP)->pP) = tmp;
			if ((iter->pP)->balance == -1) {
				iter->balance = 0;
				((iter->pP)->pR)->balance = 1;
				(iter->pP)->balance = 0;
			}
			else if ((iter->pP)->balance == 1) {
				iter->balance = 1;
				((iter->pP)->pR)->balance = 0;
				(iter->pP)->balance = 0;
			}
			else {
				iter->balance = 0;
				((iter->pP)->pR)->balance = 0;
				(iter->pP)->balance = 0;
			}
			return(1);
		}
		return(0);
	}

	int balancing_del(Node* iter) {
		if ((iter->balance == -2) && ((iter->pL)->balance <= 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = (iter->pL);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = (iter->pL);
			}
			(iter->pP) = (iter->pL);
			(iter->pL) = ((iter->pL)->pR);
			if (iter->pL != nullptr) {
				(((iter->pL)->pP)->pP) = tmp;
				(((iter->pL)->pP)->pR) = iter;
				((iter->pL)->pP) = iter;
			}
			else {
				(iter->pP)->pP = tmp;
				(iter->pP)->pR = iter;
			}
			if ((iter->pP)->balance == 0) {
				iter->balance = -1;
				(iter->pP)->balance = 1;
			}
			else {
				iter->balance = 0;
				(iter->pP)->balance = 0;
			}
			return(1);
		}
		if ((iter->balance == -2) && ((iter->pL)->balance > 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = ((iter->pL)->pR);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = ((iter->pL)->pR);
			}
			(iter->pP) = ((iter->pL)->pR);
			(iter->pL) = (((iter->pL)->pR)->pR);
			if (iter->pL != nullptr)
				((iter->pL)->pP) = (iter);
			(iter->pP)->pR = iter;
			(((iter->pP)->pP)->pR) = ((iter->pP)->pL);
			((iter->pP)->pL) = ((iter->pP)->pP);
			(((iter->pP)->pP)->pP) = (iter->pP);
			if (((iter->pP)->pL)->pR != nullptr)
				((((iter->pP)->pL)->pR)->pP) = ((iter->pP)->pP);
			((iter->pP)->pP) = tmp;
			if ((iter->pP)->balance == -1) {
				iter->balance = 1;
				((iter->pP)->pL)->balance = 0;
				(iter->pP)->balance = 0;
			}
			else if ((iter->pP)->balance == 1) {
				iter->balance = 0;
				((iter->pP)->pL)->balance = -1;
				(iter->pP)->balance = 0;
			}
			else {
				iter->balance = 0;
				((iter->pP)->pL)->balance = 0;
				(iter->pP)->balance = 0;
			}
			return(1);
		}
		if ((iter->balance == 2) && ((iter->pR)->balance >= 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = (iter->pR);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = (iter->pR);
			}
			(iter->pP) = (iter->pR);
			(iter->pR) = ((iter->pR)->pL);
			if (iter->pR != nullptr) {
				(((iter->pR)->pP)->pP) = tmp;
				(((iter->pR)->pP)->pL) = iter;
				((iter->pR)->pP) = iter;
			}
			else {
				(iter->pP)->pP = tmp;
				(iter->pP)->pL = iter;
			}
			if ((iter->pP)->balance == 0) {
				iter->balance = 1;
				(iter->pP)->balance = -1;
			}
			else {
				iter->balance = 0;
				(iter->pP)->balance = 0;
			}
			return(1);
		}
		if ((iter->balance == 2) && ((iter->pR)->balance < 0)) {
			Node* tmp = (iter->pP);
			if (tmp != nullptr) {
				if ((iter->pP)->pL == iter)
					((iter->pP)->pL) = ((iter->pR)->pL);
				else if ((iter->pP)->pR == iter)
					((iter->pP)->pR) = ((iter->pR)->pL);
			}
			(iter->pP) = ((iter->pR)->pL);
			(iter->pR) = (((iter->pR)->pL)->pL);
			if (iter->pR != nullptr)
				((iter->pR)->pP) = (iter);
			(iter->pP)->pL = iter;
			(((iter->pP)->pP)->pL) = ((iter->pP)->pR);
			((iter->pP)->pR) = ((iter->pP)->pP);
			(((iter->pP)->pP)->pP) = (iter->pP);
			if (((iter->pP)->pR)->pL != nullptr)
				((((iter->pP)->pR)->pL)->pP) = ((iter->pP)->pP);
			((iter->pP)->pP) = tmp;
			if ((iter->pP)->balance == -1) {
				iter->balance = 0;
				((iter->pP)->pR)->balance = 1;
				(iter->pP)->balance = 0;
			}
			else if ((iter->pP)->balance == 1) {
				iter->balance = -1;
				((iter->pP)->pR)->balance = 0;
				(iter->pP)->balance = 0;
			}
			else {
				iter->balance = 0;
				((iter->pP)->pR)->balance = 0;
				(iter->pP)->balance = 0;
			}
			return(1);
		}
		return(0);
	}

public:

	typedef AVL_tree_Iterator iterator;
	iterator begin() {
		return(iterator(pFirst));
	}
	iterator end() {
		return(iterator(nullptr));
	}

	AVL_tree() {
		pFirst = new Node;
		pFirst->pL = nullptr;
		pFirst->pP = nullptr;
		pFirst->pR = nullptr;
		sz = 1;
	}
	~AVL_tree() {
		Node* p;
		Node* tmp;
		p = pFirst;
		while ((pFirst->pR != nullptr) && (pFirst->pL != nullptr))
		{
			if (p->pL != nullptr) {
				p = p->pL;
				continue;
			}
			if (p->pR != nullptr) {
				p = p->pR;
				continue;
			}
			tmp = p;
			p = p->pP;
			delete tmp;
		}
		delete pFirst;
	}
	size_t size() {
		return(sz);
	}

	void Insert(T Duo) {
		sz++;
		Node* node = new Node{ Duo };
		Node* iter = pFirst;
		int H = 0;
		while (true) {
			if (node->Duo >= iter->Duo) {
				if (iter->pR != nullptr)
					iter = iter->pR;
				else {
					node->pP = iter;
					iter->pR = node;
					break;
				}
			}
			else {
				if (iter->pL != nullptr)
					iter = iter->pL;
				else {
					node->pP = iter;
					iter->pL = node;
					break;
				}
			}
		}
		if ((iter->pL == nullptr) || (iter->pR == nullptr))
			H = 1;
		if (H == 0)
			iter->balance = 0;
		else if (iter->pL == node)
			iter->balance = -1;
		else
			iter->balance = 1;
		while (iter != nullptr) {
			if (H != 1)
				break;
			if (iter->balance == 0) {
				iter = iter->pP;
				continue;
			}
			if (iter->pP != nullptr) {
				if ((iter->pP)->pR == iter) {
					iter = iter->pP;
					iter->balance += 1;
				}
			}
			else
				break;
			if (iter->pP != nullptr) {
				if ((iter->pP)->pL == iter) {
					iter = iter->pP;
					iter->balance -= 1;
				}
			}
			else
				break;
			if (balancing(iter)) {
				iter = iter->pP;
				H = 0;
				continue;
			}
		}
	}

	void Delete(T Duo) {
		sz--;
		Node* iter = pFirst;
		Node* tmp;
		int check = 0;
		int check_sheet = 0;
		while (iter != nullptr) {
			if (iter->Duo == Duo) {
				check = 1;
				break;
			}
			else if (iter->Duo < Duo)
				iter = iter->pR;
			else
				iter = iter->pL;
		}
		if (check == 0)
			return;
		if ((iter->pL == nullptr) && (iter->pR == nullptr))
			check_sheet = 1;
		if (iter->pP == nullptr)
			return;
		if (check_sheet == 0) {
			tmp = iter;
			if (iter->pR != nullptr) {
				iter = iter->pR;
				while (iter->pL != nullptr)
					iter = iter->pL;
				tmp->Duo = iter->Duo;
				check_sheet = 1;
			}
			else if (iter->pL != nullptr) {
				iter = iter->pL;
				tmp->Duo = iter->Duo;
				check_sheet = 1;
			}
		}
		if (check_sheet) {
			if (((iter->pP)->pR != nullptr) && ((iter->pP)->pL != nullptr) && (((iter->pP)->pL)->pR == nullptr) && (((iter->pP)->pL)->pL == nullptr) && (((iter->pP)->pR)->pR == nullptr) && (((iter->pP)->pR)->pL == nullptr)) {
				if ((iter->pP)->pR == iter) {
					((iter->pP)->balance) -= 1;
					(iter->pP)->pR = nullptr;
				}
				if ((iter->pP)->pL == iter) {
					((iter->pP)->balance) += 1;
					(iter->pP)->pL = nullptr;
				}
				tmp = iter;
				delete tmp;
				return;
			}
			if (((iter->pP)->pP == nullptr) && (((iter->pP)->pR == nullptr) || ((iter->pP)->pL == nullptr))) {
				(iter->pP)->balance = 0;
				if ((iter->pP)->pR == iter) {
					(iter->pP)->pR = nullptr;
				}
				if ((iter->pP)->pL == iter) {
					(iter->pP)->pL = nullptr;
				}
				tmp = iter;
				delete tmp;
				return;
			}
			if (((iter->pP)->pP)->balance == 0) {
				tmp = iter;
				(iter->pP)->balance = 0;
				if ((iter->pP)->pR == iter) {
					(iter->pP)->pR = nullptr;
				}
				if ((iter->pP)->pL == iter) {
					(iter->pP)->pL = nullptr;
				}
				iter = iter->pP;
				if ((iter->pP)->pR == iter)
					((iter->pP)->balance) -= 1;
				if ((iter->pP)->pL == iter)
					((iter->pP)->balance) += 1;
				delete tmp;
				return;
			}
			tmp = iter;
			if ((iter->pP)->pR == iter) {
				((iter->pP)->balance) -= 1;
				(iter->pP)->pR = nullptr;
			}
			if ((iter->pP)->pL == iter) {
				((iter->pP)->balance) += 1;
				(iter->pP)->pL = nullptr;
			}
			iter = iter->pP;
			delete tmp;
			while (iter->pP != nullptr) {
				if ((iter->pP)->balance == 0) {
					if ((iter->pP)->pR == iter)
						((iter->pP)->balance) -= 1;
					if ((iter->pP)->pL == iter)
						((iter->pP)->balance) += 1;
					return;
				}
				if (balancing_del(iter)) {
					if ((iter->pP)->balance != 0)
						return;
					else {
						iter = iter->pP;
						continue;
					}
				}
				if ((iter->pP)->pR == iter)
					((iter->pP)->balance) -= 1;
				if ((iter->pP)->pL == iter)
					((iter->pP)->balance) += 1;
				iter = iter->pP;
			}
		}
	}

	T& operator[](int N) {
		T A;
		int k = 0;
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if (k == N) {
				return((*it).Duo);
			}
			k++;
		}
		return(A);
	}

};

template<typename T> class List {

	struct Node
	{
		T Duo;
		Node* pNext;
		friend bool operator==(const Node& a, const Node& b)
		{
			if (a.Duo != b.Duo)
				return(false);
			if ((a.pNext != nullptr) && (b.pNext != nullptr)) {
				if (a.pNext->Duo != b.pNext->Duo)
					return(false);
			}
			else
				if (a.pNext != b.pNext)
					return(false);
			return(true);
		}
	};

	Node* pFirst;
	size_t sz;

	class ListIterator {
		friend class List;
	public:
		typedef Node iterator_type;
		typedef input_iterator_tag iterator_category;
		typedef iterator_type iterator_value;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

	private:
		iterator_type* value;
	public:
		ListIterator(Node* p) : value(p) {}
		ListIterator(ListIterator& it) : value(it.value) {}
		ListIterator(const ListIterator& it) : value(it.value) {}
		typename ListIterator::reference operator*() {
			return(*value);
		}
		ListIterator& operator++() {
			if (value->pNext == nullptr)
				value = nullptr;
			else
				value = value->pNext;
			return(*this);
		}
		bool operator!=(ListIterator const& other) {
			return(value != other.value);
		}
		bool operator==(ListIterator const& other) {
			return(!(value != other.value));
		}
	};

public:
	List() {
		pFirst = new Node;
		pFirst->pNext = nullptr;
		sz = 1;
	}
	~List() {
		Node* p;
		while (pFirst->pNext != nullptr)
		{
			p = pFirst;
			pFirst = pFirst->pNext;
			delete p;
		}
		delete pFirst;
	}
	List(const List& A) {
		pFirst = A.pFirst;
		sz = A.sz;
		Node* pNew = pFirst = new Node{ *A.pFirst };
		for (; pNew->pNext != nullptr; pNew = pNew->pNext)
			pNew->pNext = new Node{ *pNew->pNext };
	}
	size_t size() {
		return(sz);
	}
	T& Front() {
		return(pFirst->Duo);
	}
	void PopFront() {
		if (sz > 1) {
			Node* p = pFirst;
			pFirst = pFirst->pNext;
			delete p;
			sz--;
		}
	}
	void PushFront(T& Duo) {
		Node* node = new Node{ Duo, pFirst };
		pFirst = node;
		sz++;
	}
	void PushBack(T& Duo) {
		Node* node = new Node{ Duo, nullptr };
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if ((*it).pNext == nullptr) {
				(*it).pNext = node;
				sz++;
				break;
			}
		}
	}
	typedef ListIterator iterator;
	iterator begin() {
		return(iterator(pFirst));
	}
	iterator end() {
		return(iterator(nullptr));
	}
	List& operator=(const List& A) {
		if (this != &A) {
			pFirst = A.pFirst;
			sz = A.sz;
			Node* pNew = pFirst = new Node{ *A.pFirst };
			for (; pNew->pNext != nullptr; pNew = pNew->pNext)
				pNew->pNext = new Node{ *pNew->pNext };
		}
		return(*this);
	}
	T& operator[](int N) {
		T A;
		int k = 0;
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if (k == N) {
				return((*it).Duo);
			}
			k++;
		}
		return(A);
	}
	void Eraise(int N) {
		if (N == 0)
			this->PopFront();
		else if (N < sz) {
			Node* res = new Node;
			int k = 0;
			for (iterator it = this->begin(); it != this->end(); ++it) {
				if (k == N) {
					*res = (*it);
					break;
				}
				k++;
			}
			k = 0;
			for (iterator it = this->begin(); it != this->end(); ++it) {
				if (k == N - 1) {
					(*it).pNext = res->pNext;
					break;
				}
				k++;
			}
			delete res;
			sz--;
		}
	}
	friend bool operator==(const List& a, const List& b)
	{
		if (a.sz != b.sz)
			return(false);
		List A = a;
		List B = b;
		iterator it1 = A.begin();
		iterator it2 = B.begin();
		while ((it1 != A.end()) || (it2 != B.end())) {
			Node p1 = *it1;
			Node p2 = *it2;
			if (!(p1 == p2))
				return(false);
			++it1;
			++it2;
		}
		return(true);
	}
};

class Polynom {
	List<Pair<double, int>> Pol;
public:

	//Polynom(const Polynom& A) : Pol(A.Pol) {}

	Polynom() {
		Pol[0].First = 0;
		Pol[0].Second = -100;
	}
	Polynom(string str) {
		Pol[0].First = 0;
		Pol[0].Second = -100;
		this->parse(str);
	}

	//Polynom& operator=(const Polynom& A) {
	//	if (this != &A) {
	//		this->Pol = A.Pol;
	//	}
	//	return(*this);
	//}

	Pair<double, int> str_to_pair(string str) {
		Pair<double, int> Duo{ 0,0 };
		double flag = 1;
		if (str[0] == '-')
			flag *= -1;
		str.erase(0, 1);
		if ((str[0] < '0') || (str[0] > '9'))
			Duo.First = flag;
		else {
			string coef = "";
			while (1) {
				if ((str[0] >= '0') && (str[0] <= '9') || (str[0] == '.')) {
					coef.push_back(str[0]);
					str.erase(0, 1);
				}
				else
					break;
			}
			double tmp = stod(coef);
			Duo.First = tmp * flag;
		}
		int tmp = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == 'x') {
				if ((i + 2 < str.length()) && (str[i + 2] >= '0') && (str[i + 2] <= '9'))
					tmp += 100 * (str[i + 2] - '0');
				else
					tmp += 100;
			}
			if (str[i] == 'y') {
				if ((i + 2 < str.length()) && (str[i + 2] >= '0') && (str[i + 2] <= '9'))
					tmp += 10 * (str[i + 2] - '0');
				else
					tmp += 10;
			}
			if (str[i] == 'z') {
				if ((i + 2 < str.length()) && (str[i + 2] >= '0') && (str[i + 2] <= '9'))
					tmp += (str[i + 2] - '0');
				else
					tmp += 1;
			}
		}
		Duo.Second = tmp;
		return(Duo);
	}
	void parse(string str) {
		vector<Pair<double,int>> monoms;
		string tmp = "";
		if (str[0] != '-')
			tmp += '+';
		for (int i = 0; i < str.length() + 1; i++) {
			if ((i > 0) && ((str[i] == '+') || (str[i] == '-') || (i == str.length()))) {
				Pair<double, int> p = str_to_pair(tmp);
				monoms.push_back(p);
				tmp = "";
			}
			tmp += str[i];
		}
		sort(monoms.begin(), monoms.end());
		for (int i = 0; i < monoms.size(); i++) {
			Pol.PushFront(monoms[i]);
		}
	}
	friend ostream& operator<<(ostream& os, Polynom& A)
	{
		for (List<Pair<double,int>>::iterator it = A.Pol.begin(); it != A.Pol.end(); ++it) {
			if (A.Pol.size() <= 1) {
				cout << 0;
				return os;
			}
			double Coef = (*it).Duo.First;
			int Deg = (*it).Duo.Second;
			if (Coef == 0)
				continue;
			if (Deg == 0) {
				if ((it == A.Pol.begin()) && (Coef > 0))
					cout << Coef;
				else if (Coef > 0)
					cout << '+' << Coef;
				else
					cout << Coef;
				continue;
			}
			if ((it != A.Pol.begin()) && (Coef == 1))
				cout << '+';
			else if (Coef == 1);
			else if (Coef == -1)
				cout << '-';
			else {
				if ((it == A.Pol.begin()) && (Coef > 1))
					cout << Coef;
				else if (Coef > 1)
					cout << '+' << Coef;
				else
					cout << Coef;
			}
			int tmp[3] = { 0 };
			for (int i = 2; i >= 0; i--) {
				tmp[i] = Deg % 10;
				Deg /= 10;
			}
			if (tmp[0] == 1)
				cout << 'x';
			if (tmp[0] > 1)
				cout << "x^" << tmp[0];
			if (tmp[1] == 1)
				cout << 'y';
			if (tmp[1] > 1)
				cout << "y^" << tmp[1];
			if (tmp[2] == 1)
				cout << 'z';
			if (tmp[2] > 1)
				cout << "z^" << tmp[2];
		}
		return os;
	}
	friend istream& operator>>(istream& is, Polynom& A) {
		string str = "";
		getline(cin, str);
		while (1) {
			int i = str.find(' ');
			if ((i < 0) || i >= str.length())
				break;
			str.erase(i, 1);
		}
		A.parse(str);
		return is;
	}
	friend Polynom operator*(double Const, Polynom A) {
		for (List<Pair<double,int>>::iterator it = A.Pol.begin(); it != A.Pol.end(); ++it) {
			(*it).Duo.First *= Const;
		}
		return (A);
	}
	Polynom operator*(double Const) {
		for (List<Pair<double, int>>::iterator it = this->Pol.begin(); it != this->Pol.end(); ++it) {
			(*it).Duo.First *= Const;
		}
		return(*this);
	}
	Polynom operator+(Polynom& A) {
		Polynom tmp;
		List<Pair<double, int>>::iterator it1 = this->Pol.begin();
		List<Pair<double, int>>::iterator it2 = A.Pol.begin();
		Pair<double,int> Duo = { 0,0 };
		while ((it1 != this->Pol.end()) || (it2 != A.Pol.end())) {
			if ((*it1).Duo.Second > (*it2).Duo.Second) {
				Duo = (*it1).Duo;
				++it1;
			}
			else if ((*it1).Duo.Second < (*it2).Duo.Second) {
				Duo = (*it2).Duo;
				++it2;
			}
			else {
				Duo.First = (*it2).Duo.First + (*it1).Duo.First;
				Duo.Second = (*it2).Duo.Second;
				++it1;
				++it2;
			}
			if (Duo.First != 0)
				tmp.Pol.PushBack(Duo);
		}
		if (tmp.Pol.size() > 1) {
			Duo = tmp.Pol.Front();
			tmp.Pol.PopFront();
			tmp.Pol.PushBack(Duo);
		}
		return(tmp);
	}
	Polynom operator*(Polynom& A) {
		Polynom res;
		for (List<Pair<double, int>>::iterator it1 = this->Pol.begin(); it1 != this->Pol.end(); ++it1) {
			if ((*it1).Duo.First == 0)
				continue;
			Polynom tmp;
			for (List<Pair<double, int>>::iterator it2 = A.Pol.begin(); it2 != A.Pol.end(); ++it2) {
				if ((*it2).Duo.First == 0)
					continue;
				Pair<double,int> Duo = { (*it1).Duo.First * (*it2).Duo.First,(*it1).Duo.Second + (*it2).Duo.Second };
				if (Duo.Second > 999)
					throw out_of_range("incorrect degree");
				tmp.Pol.PushBack(Duo);
			}
			if (tmp.Pol.size() > 1) {
				Pair<double,int> Duo = tmp.Pol.Front();
				tmp.Pol.PopFront();
				tmp.Pol.PushBack(Duo);
			}
			res = res + tmp;
		}
		return(res);
	}
	double value(double a, double b, double c) {
		double res = 0;
		for (List<Pair<double, int>>::iterator it = this->Pol.begin(); it != this->Pol.end(); ++it) {
			double coef = (*it).Duo.First;
			int deg = (*it).Duo.Second;
			if (coef) {
				double tmp = coef * (binpow(a, (deg / 100))) * (binpow(b, ((deg % 100) / 10))) * (binpow(c, (deg % 10)));
				res += tmp;
			}
		}
		return(res);
	}
	friend Polynom operator-(Polynom A, Polynom B) {
		B = B * (-1);
		return(A + B);
	}
	friend bool operator==(const Polynom& a, const Polynom& b)
	{
		if (a.Pol == b.Pol)
			return(true);
		else
			return(false);
	}
};