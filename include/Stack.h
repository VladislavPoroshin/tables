#pragma once
#include <iostream>
using namespace std;
typedef long long unsigned int llui;
typedef long long int lli;

template<typename T>
class Stack {

	lli top;
	llui size;
	T* mass;

public:
	friend void swap(Stack& L, Stack& R) {
		swap(L.size, R.size);
		swap(L.mass, R.mass);
		swap(L.top, R.top);
	}
	Stack() {
		top = -1;
		size = 1;
		mass = new T[size];
	}
	Stack(llui len) {
		if (len <= 0)
			throw out_of_range("length must be greater than zero");
		top = -1;
		size = len;
		mass = new T[size];
	}
	Stack(const Stack& A) {
		top = A.top;
		size = A.size;
		mass = new T[size];
		copy(A.mass, A.mass + size, mass);
	}
	Stack(Stack&& A) {
		mass = nullptr;
		swap(A, *this);
	}
	~Stack() {
		delete[] mass;
	}
	Stack& operator=(const Stack& A) {
		if (this == &A)
			return(*this);
		if (size != A.size) {
			T* tmp = new T[A.size];
			delete[] mass;
			size = A.size;
			mass = tmp;
		}
		copy(A.mass, A.mass + size, mass);
		return(*this);
	}
	Stack& operator=(Stack&& A) {
		swap(A, *this);
		return(*this);
	}
	bool operator==(const Stack& A) const
	{
		if ((size != A.size) || (top != A.top))
			return(false);
		for (llui i = 0; i < size; i++)
			if (mass[i] != A.mass[i])
				return(false);
		return(true);
	}
	bool operator!=(const Stack& A) const
	{
		return(!(*this == A));
	}
	llui Size() const { return(top + 1); } //сколько элементов лежит в стеке
	bool IsFull() const { return(top == size - 1); }
	bool IsEmpty() const { return(top == -1); }
	T Pop() { if (IsEmpty()) throw out_of_range("Stack is empty"); else return(mass[top--]); }
	T Top() const { if (IsEmpty()) throw out_of_range("Stack is empty"); else return(mass[top]); } //посмотреть что на вершине стека
	void Push(const T& Elem) {
		if (IsFull()) {
			T* tmp = new T[size * 2];
			copy(mass, mass + size, tmp);
			delete[] mass;
			mass = tmp;
			size *= 2;
		}
		mass[++top] = Elem;
	}
};