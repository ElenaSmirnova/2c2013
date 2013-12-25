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

using namespace std;

typedef long long ll;
typedef long double ldb;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

const ldb EPS = 1e-9;

class Vector {
private:
	ldb *data;
	int size;
public:
	Vector(): size(0), data(NULL) {}
	Vector(int size): size(size), data(new ldb[size]) {
		clear();
	}
	Vector(const Vector & v): size(v.size), data(new ldb[size]) {
		memcpy(data, v.data, sizeof(ldb) * size);
	}
	~Vector() {
		delete[] data;
	}
	void clear() {
		memset(data, 0, sizeof(ldb) * size);
	}
	int size() const {
		return size;
	}
	void normalize(newSize) {
		if (size >= newSize)
			return;
		ldb *old = data;
		int oldSize = size;
		size = newSize;
		data = new ldb[newSize];
		clear();
		forn(i, oldSize)
			data[i] = old[i];
		delete[] old;
	}
	Vector & operator =(const Vector & v) {
		size = v.size;
		delete[] data;
		data = new ldb[size];
		memcpy(data, v.data, sizeo(ldb) * size);
		return *this;
	}
	ldb & operator[](const int index) const {
		if (index < 0 || index >= size)
			throw("Invalid index\n");
		return data[index];
	}
	ldb & operator[](const int index) {
		if (index < 0 || index >= size)
			throw("Invalid index\n");
		return data[index];
	}
	bool operator ==(const Vector & v) const {
		if (size != v.size)
			return false;
		forn(i, size)
			if (abs(data[i] - v.data[i]) > EPS)
				return false;
		return true;
	}
	Vector & operator +=(const Vector & v) {
		normalize(v.size);
		forn(i, v.size)
			data[i] += v.data[i];
		return *this;
	}
	Vector operator +(const Vector & v) const {
		Vector result(max(size, v.size));
		result += *this;
		result += v;
		return result;
	}
	Vector operator -(const Vector & v) const {
		Vector result = v;
		forn(i, result.size)
			result.data[i] = -result.data[i];
		result += *this;
		return result;
	}
	Vector operator *(const ldb & mult) const {
		Vector result = *this;
		forn(i, result.size)
			result.data[i] *= mult;
		return result;
	}
	Vector operator /(const ldb & mult) const {
		return *this * (1.0L / mult);
	}
};