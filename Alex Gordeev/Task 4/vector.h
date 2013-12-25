#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <iomanip>
#include "common.h"

using namespace std;

typedef unsigned int uint;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

class Vector {
private:
	uint *data;
	int size;
public:
	Vector(): size(0), data(NULL) {}
	Vector(int size): size(size), data(new uint[size]) {
		clear();
	}
	Vector(const Vector & v): size(v.size), data(new uint[size]) {
		memcpy(data, v.data, sizeof(uint) * size);
	}
	~Vector() {
		delete[] data;
	}
	void clear() {
		memset(data, 0, sizeof(uint) * size);
	}
	int getSize() const {
		return size;
	}
	void normalize(const int newSize) {
		if (size >= newSize)
			return;
		uint *old = data;
		int oldSize = size;
		size = newSize;
		data = new uint[newSize];
		clear();
		forn(i, oldSize)
			data[i] = old[i];
		delete[] old;
	}
	Vector & operator =(const Vector & v) {
		size = v.size;
		delete[] data;
		data = new uint[size];
		memcpy(data, v.data, sizeof(uint) * size);
		return *this;
	}
	uint & operator[](const int ind) const {
		if (ind < 0 || ind >= size)
			throw("Invalid index\n");
		return data[ind];
	}
	uint & operator[](const int index) {
		if (index < 0 || index >= size)
			throw("Invalid index\n");
		return data[index];
	}
	bool operator ==(const Vector & v) const {
		if (size != v.size)
			return false;
		forn(i, size)
			if (data[i] != v.data[i])
				return false;
		return true;
	}
	Vector & operator +=(const Vector & v) {
		normalize(v.size);
		forn(i, v.size)
			data[i] = (data[i] + v.data[i]) % MOD;
		return *this;
	}
	Vector operator +(const Vector & v) const {
		Vector res(max(size, v.size));
		res += *this;
		res += v;
		return res;
	}
	Vector operator -(const Vector & v) const {
		Vector res(v);
		forn(i, res.size)
			res.data[i] = (-res.data[i] + MOD) % MOD;
		res += *this;
		return res;
	}
	Vector operator *(const uint & mult) const {
		Vector res(*this);
		forn(i, res.size)
			res.data[i] = (res.data[i] * mult) % MOD;
		return res;
	}
	Vector operator /(const uint & mult) const {
		return *this * invert(mult);
	}
	uint dotProduct(const Vector & v) const {
		uint res = 0;
		forn(i, min(size, v.size))
			res = (res + data[i] * v.data[i]) % MOD;
		return res;
	}
};
