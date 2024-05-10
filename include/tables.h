#pragma once
#include "polynom.h"

unsigned int hash_1(string A, int N) {
	Polynom B("x^2y^2z^2-xyz");
	double res = 0;
	for (auto elem : A) {
		res += (unsigned int)(elem);
	}
	return((unsigned int)(B.value(res, res, res)) % N);
}

template<typename Key, typename Value> class array_un_table {
	vector<Pair<Key, Value>> data{};
public:
	Value* Find(Key key) {
		for (auto& rec : data) {
			if (rec.First == key)
				return &rec.Second;
		}
		return nullptr;
	}
	void Insert(Key key, Value value) {
		if (Find(key))
			return;
		data.push_back({ key,value });
	}
	void Delete(Key key) {
		int i = 0;
		for (auto& rec : data) {
			if (rec.First == key) {
				data.erase(data.begin() + i);
				break;
			}
			i++;
		}
		return;
	}
	friend ostream& operator<<(ostream& os, array_un_table& table)
	{
		for (auto& rec : table.data) {
			cout << rec.First << " = " << rec.Second << endl;
		}
		return os;
	}
};

template<typename Key, typename Value> class list_un_table {
	List<Pair<Key, Value>> data;
public:
	Value* Find(Key key) {
		for (auto& rec : data) {
			if (rec.Duo.First == key)
				return &rec.Duo.Second;
		}
		return nullptr;
	}
	void Insert(Key key, Value value) {
		if (Find(key))
			return;
		Pair<Key, Value> tmp = { key,value };
		data.PushBack(tmp);
	}
	void Delete(Key key) {
		int i = 0;
		for (auto& rec : data) {
			if (rec.Duo.First == key) {
				data.Eraise(i);
				break;
			}
			i++;
		}
		return;
	}
	friend ostream& operator<<(ostream& os, list_un_table& table)
	{	
		for (auto& rec : table.data) {
			if (rec.Duo.First != "")
				cout << rec.Duo.First << " = " << rec.Duo.Second << endl;
		}
		return os;
	}
};

template<typename Key, typename Value> class AVL_tree_table {
	AVL_tree<Pair<Value, Key>> data;
public:
	Value* Find(Key key) {
		for (auto& rec : data) {
			if (rec.Duo.Second == key)
				return &rec.Duo.First;
		}
		return nullptr;
	}
	void Insert(Key key, Value value) {
		if (Find(key))
			return;
		Pair<Value, Key> tmp = { value, key };
		data.Insert(tmp);
	}
	void Delete(Key key) {
		int i = 0;
		for (auto& rec : data) {
			if (rec.Duo.Second == key) {
				data.Delete(rec.Duo);
				break;
			}
			i++;
		}
		return;
	}
	friend ostream& operator<<(ostream& os, AVL_tree_table& table)
	{
		for (auto& rec : table.data) {
			if (rec.Duo.Second != "")
				cout << rec.Duo.Second << " = " << rec.Duo.First << endl;
		}
		return os;
	}
};

template<typename Key, typename Value> class array_table {
	vector<Pair<Key, Value>> data{};
public:
	Value* Find(Key key) {
		int l = 0;
		int r = data.size() - 1;
		while ((l <= r) && (r >= 0)) {
			int mid = (l + r) / 2;
			if (data[mid].First == key) 
				return &(data[mid].Second);
			if (data[mid].First > key) 
				r = mid - 1;
			else 
				l = mid + 1;
		}
		return nullptr;
	}
	void Insert(Key key, Value value) {
		int mid = -1;
		int l = 0;
		int r = data.size() - 1;
		while ((l <= r) && (r >= 0)) {
			mid = (l + r) / 2;
			if (data[mid].First == key)
				return;
			if (data[mid].First > key)
				r = mid - 1;
			else
				l = mid + 1;
		}
		Pair<Key, Value> tmp = { key,value };
		if (mid != -1) {
			if (data[mid].First > key)
				data.insert(data.begin() + mid, tmp);
			else
				data.insert(data.begin() + mid + 1, tmp);
		}
		else
			data.push_back(tmp);
	}
	void Delete(Key key) {
		int l = 0;
		int r = data.size() - 1;
		while ((l <= r) && (r >= 0)) {
			int mid = (l + r) / 2;
			if (data[mid].First == key) {
				data.erase(data.begin() + mid);
				return;
			}
			if (data[mid].First > key)
				r = mid - 1;
			else
				l = mid + 1;
		}
		return;
	}
	friend ostream& operator<<(ostream& os, array_table& table)
	{
		for (auto& rec : table.data) {
			cout << rec.First << " = " << rec.Second << endl;
		}
		return os;
	}
};

class first_hash_table {

	int M;
	vector<List<Pair<string, Polynom>>> data;

public:

	first_hash_table() {
		M = 1000;
		data.resize(M);
	}
	first_hash_table(int size) {
		M = size;
		data.resize(M);
	}
	Polynom* Find(string key) {
		for (auto& rec : data[hash_1(key, M)]) {
			if (rec.Duo.First == key)
				return &rec.Duo.Second;
		}
		return nullptr;
	}
	void Insert(string key, Polynom value) {
		if (Find(key))
			return;
		Pair<string, Polynom> tmp = { key,value };
		data[hash_1(key, M)].PushBack(tmp);
	}
	void Delete(string key) {
		int i = 0;
		unsigned int tmp = hash_1(key, M);
		for (auto& rec : data[tmp]) {
			if (rec.Duo.First == key) {
				data[tmp].Eraise(i);
				break;
			}
			i++;
		}
		return;
	}
	friend ostream& operator<<(ostream& os, first_hash_table& table)
	{
		int i = 0;
		while (i < table.M) {
			for (auto& rec : table.data[i]) {
				if (rec.Duo.First != "")
					cout << rec.Duo.First << " = " << rec.Duo.Second << endl;
			}
			i++;
		}
		return os;
	}
};

class second_hash_table {

	int skip;
	int p;
	int M;
	vector<Pair<string, Polynom>> data{};

public:

	second_hash_table() {
		M = 1000;
		p = 7;
		skip = 0;
		data.resize(M);
	}
	second_hash_table(int size) {
		if (size % 2 == 0) {
			M = size + 1;
			p = 2;
			skip = 1;
		}
		else {
			M = size;
			p = 2;
			skip = 0;
		}
		data.resize(M);
	}
	Polynom* Find(string key) {
		int tmp = hash_1(key, M);
		int score = 0;
		while (true) {
			if ((skip) && (tmp == M - 1)) {
				tmp = (p + tmp) % M;
				continue;
			}
			if (data[tmp].First == key)
				return (&(data[tmp].Second));
			if (data[tmp].First == "")
				return nullptr;
			tmp = (p + tmp) % M;
			score++;
			if (score == M)
				return nullptr;
		}
	}
	void Insert(string key, Polynom value) {
		if (key == "-1")
			return;
		if (Find(key))
			return;
		Pair<string, Polynom> tmp_1 = { key,value };
		int tmp_2 = hash_1(key, M);
		int score = 0;
		while (true) {
			if ((skip) && (tmp_2 == M - 1)) {
				tmp_2 = (p + tmp_2) % M;
				continue;
			}
			if ((data[tmp_2].First == "-1") || (data[tmp_2].First == "")) {
				data[tmp_2] = tmp_1;
				return;
			}
			tmp_2 = (p + tmp_2) % M;
			score++;
			if (score == M)
				return;
		}
	}
	void Delete(string key) {
		int tmp = hash_1(key, M);
		int score = 0;
		while (true) {
			if ((skip) && (tmp == M - 1)) {
				tmp = (p + tmp) % M;
				continue;
			}
			if (data[tmp].First == key) {
				data[tmp].First = "-1";
				return;
			}
			if (data[tmp].First == "") {
				return;
			}
			tmp = (p + tmp) % M;
			score++;
			if (score == M)
				return;
		}
	}
	friend ostream& operator<<(ostream& os, second_hash_table& table)
	{
		for (auto& rec : table.data) {
			if ((rec.First != "") && (rec.First != "-1"))
				cout << rec.First << " = " << rec.Second << endl;
		}
		return os;
	}
};