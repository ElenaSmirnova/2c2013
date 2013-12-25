#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;


class Vector {
	private:
	int * data;
	int n;
	static const int MOD = 251;
	public:
	Vector& operator = (const Vector & other) {
		n = other.n;
		delete[] data;
		data = new int[n];
		memcpy(data, other.data, sizeof(int) * n);
		return *this;
	}
	Vector(const Vector & other) {
		n = other.n;
		data = new int[n];
		memcpy(data, other.data, sizeof(int) * n);
	}
	Vector() : data(NULL), n(0) {};
	Vector(int _n) : data(new int[_n]), n(_n) {
		clear();
	}
	Vector(int _n, int * _data) : data(_data), n(_n) {};
	~Vector() {
		delete[] data;
	}
	void clear() {
		memset(data, 0, n * sizeof(int));
	}
	int size() const {
		return n;
	}
	void resize(int newSize) {
		int * t = data;
		data = new int[newSize];
		int mn = min(n, newSize);
		n = newSize;
		clear();
		for (int i = 0; i < mn; ++i) {
			data[i] = t[i];
		}
		delete[] t;
	}
	void normalize(int newSize) {
		if (n < newSize)
			this->resize(newSize);
	}
	Vector mod() {
		for (int i = 0; i < n; ++i) {
			data[i] = (data[i] %MOD + MOD) % MOD;
		}
		return *this;
	}
	int get(int pos) const{
		if (pos >= n) {
			throw("Invalid index");
		}
		return data[pos];
	}
	void set(int pos, int x) {
		if (pos >= n) {
			throw("Invalid index");
		}
		data[pos] = x;
	}
	Vector clone() const {
		Vector w(n);
		w = w + (*this);
		return w;
	}
	Vector operator + (const Vector & other) const {
		int newSize = max(n, other.size());
		Vector w(newSize);
		for (int i = 0; i < newSize; ++i) {
			if (i < size())
				w.set(i, w.get(i) + get(i));
			if (i < other.size())
				w.set(i, w.get(i) + other.get(i));
		}
		w.mod();
		return w;
	}
	Vector& operator += (const Vector & other) {
		this->normalize(other.size());
		for (int i = 0; i < other.size(); ++i) {
			this->data[i] += other.get(i);
		}
		this->mod();
		return *this;
	}
	Vector operator * (int d) const {
		Vector w = this->clone();
		for (int i = 0; i < size(); ++i) {
			w.set(i, w.get(i) * d);
		}
		w.mod();
		return w;
	}
	Vector& operator *= (int d) {
		for (int i = 0; i < size(); ++i) {
			(*this).set(i, (*this).get(i) * d);
		}
		this->mod();
		return *this;
	}
	Vector operator - (const Vector & other) const {
		return (*this + other * (-1)).mod();
	}
	Vector& operator -= (const Vector & other) {
		this->normalize(other.size());
		for (int i = 0; i < other.size(); ++i) {
			this->data[i] -= other.get(i);
		}
		this->mod();
		return *this;
	}
	Vector operator / (int d) const {
		Vector w = this->clone();
		for (int i = 0; i < size(); ++i) {
			w.set(i, w.get(i) / d);
		}
		return w;
	}
	Vector& operator /= (int d) {
		for (int i = 0; i < size(); ++i) {
			(*this).set(i, (*this).get(i) / d);
		}
		return *this;
	}
	int operator * (const Vector & other) const {
		int w = 0;
		for (int i = 0; i < min(size(), other.size()); ++i) {
			w += get(i) * other.get(i);
		}
		return w % MOD;
	}
	bool operator == (const Vector & other) const {
		if (size() != other.size())
			return false;
		for (int i = 0; i < n; ++i) {
			if (get(i) % MOD != other.get(i) % MOD)
				return false;
		}
		return true;
	}
	void read() {
		int nn;
		cin >> nn;
		resize(nn);
		for (int i = 0; i < nn; ++i) {
			cin >> data[i];
		}
		mod();
	}
	void print() {
		cout << "Vector:\n";
		cout << fixed << setprecision(6);
		for (int i = 0; i < n; ++i) {
			cout << data[i] << ' ';
		}
		cout << endl;
	}
};




