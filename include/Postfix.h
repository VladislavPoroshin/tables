#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Stack.h"
using namespace std;
typedef long long unsigned int llui;
typedef long long int lli;

class Postfix {
	string infix;
	string postfix;
public:
	Postfix() {
		infix = "";
		postfix = "";
	}
	Postfix(string A) {
		infix = A;
		postfix = this->ToPostfix();
	}
	bool Parse(string A) {
		Stack<string> ST;
		bool flag = true;
		map<char, int> items;
		items = {
		{ '+', 1}, { '-', 1}, { '*', 1},
		{ '(', 0}, { ')', 0}
		};
		for (int i = 0; i < A.size(); i++) {
			auto iter = items.find(A[i]);
			int id;
			if (iter != items.end()) {
				id = (items.find(A[i]))->second;
			}
			else {
				id = -1;
			}
			switch (id) {
			default:
			{
				while (true) {
					if (i == A.size())
						break;
					auto iter_1 = items.find(A[i]);
					if (iter_1 != items.end()) {
						id = (items.find(A[i]))->second;
						break;
					}
					else {
						id = -1;
					}
					i++;
				}
				i--;
				id = -1;
				if (i != A.size() - 1) {
					auto iter_next = items.find(A[i + 1]);
					if (iter_next != items.end()) {
						int id_next = (items.find(A[i + 1]))->second;
						if (id == id_next)
							return(!flag);
						if (A[i + 1] == '(')
							return(!flag);
					}
				}
				break;
			}
			case 0:
			{
				if (A[i] == '(')
					ST.Push("(");
				if (A[i] == ')') {
					if (!ST.IsEmpty())
						ST.Pop();
					else
						return(!flag);
				}
				if (i != A.size() - 1) {
					auto iter_next = items.find(A[i + 1]);
					if (iter_next != items.end()) {
						int id_next = (items.find(A[i + 1]))->second;
						if ((id_next == 1) && (A[i + 1] != '-') && (A[i] == '('))
							return(!flag);
						if ((id_next == 2) && (A[i] == ')'))
							return(!flag);
						if ((A[i] == '(') && (A[i] == ')'))
							return(!flag);
					}
				}
				break;
			}
			case 1:
			{
				if ((i == 0) && (A[i] != '-'))
					return(!flag);
				if (i == A.size() - 1)
					return(!flag);
				else {
					auto iter_next = items.find(A[i + 1]);
					if (iter_next != items.end()) {
						int id_next = (items.find(A[i + 1]))->second;
						if (id == id_next)
							return(!flag);
						if (A[i + 1] == ')')
							return(!flag);
					}
				}

				break;
			}
			}
		}
		if (!ST.IsEmpty())
			return(!flag);
		return(flag);
	}
	string GetInfix() {
		return(infix);
	}
	string GetPostfix() {
		return(postfix);
	}
	string ToPostfix() {
		Stack<string> ST;
		string tmp = "";
		if (!Parse(infix)) {
			throw out_of_range("incorrect expression");
			return(tmp);
		}
		for (int i = 0; i < infix.size(); i++) {
			switch (infix[i])
			{
			default:
			{
				while ((infix[i] != '(') && (infix[i] != ')') && (infix[i] != '+') && (infix[i] != '-') && (infix[i] != '*')) {
					tmp.push_back(infix[i]);
					if (i >= infix.size() - 1) {
						i++;
						break;
					}
					i++;
				}
				tmp.push_back(' ');
				i--;
				break;
			}
			case '(':
			{
				string elem = "";
				elem += infix[i];
				ST.Push(elem);
				break;
			}
			case ')':
			{
				string item = ST.Pop();
				while (item != "(") {
					tmp += item;
					item = ST.Pop();
				}
				break;
			}
			case '+':
			case '-':
			case '*':
			{
				map<string, int> priority;
				priority = { { "+", 1}, { "-", 1}, { "*", 2} };
				if ((i == 0) && (infix[i] == '-'))
					tmp.push_back('0');
				if ((i > 0) && (infix[i] == '-') && (infix[i - 1] == '('))
					tmp.push_back('0');
				while (!ST.IsEmpty()) {
					string item = ST.Pop();
					if (item == "(") {
						ST.Push(item);
						break;
					}
					else {
						string elem = "";
						elem += infix[i];
						int id1 = (priority.find(elem))->second;
						int id2 = (priority.find(item))->second;
						if (id1 <= id2)
							tmp += item;
						else {
							ST.Push(item);
							break;
						}
					}
				}
				string elem = "";
				elem += infix[i];
				ST.Push(elem);
				break;
			}
			}
		}
		while (!ST.IsEmpty()) {
			string item = ST.Pop();
			tmp += item;
		}
		postfix = tmp;
		return(postfix);
	}
};