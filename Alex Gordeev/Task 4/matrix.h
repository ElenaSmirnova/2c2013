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
#include "vector.h"

using namespace std;

typedef unsigned int uint;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)


class Matrix {
private:
	Vector *data;
	int rows, columns;
public:
	Matrix(): data(NULL), rows(0), columns(0) {}
	Matrix(int rows, int columns): rows(rows), columns(columns), data(new Vector[rows]) {
		forn(i, rows)
			data[i] = Vector(columns);
	}
	Matrix(const Matrix & m): rows(m.rows), columns(m.columns), data(new Vector[m.rows]) {
		forn(i, rows)
			data[i] = Vector(m[i]);
	}
	~Matrix() {
		delete[] data;
	}
	int getSize() const {
		return rows * columns;
	}
	int getRows() const {
		return rows;
	}
	int getColumns() const {
		return columns;
	}
	Matrix & operator =(const Matrix & m) {
		rows = m.rows, columns = m.columns;
		delete[] data;
		data = new Vector[rows];
		forn(i, rows)
			data[i] = Vector(m[i]);
		return *this;
	}
	Vector & operator [](const int ind) const {
		if (ind < 0 || ind >= rows)
			throw("Invalid index\n");
		return data[ind];
	}
	Vector & operator [](const int ind) {
		if (ind < 0 || ind >= rows)
			throw("Invalid index\n");
		return data[ind];
	}
	Matrix transpose() const {
		Matrix res(columns, rows);
		forn(i, rows)
			forn(j, columns)
				res.data[j][i] = data[i][j];
		return res;
	}
	Matrix getMinor(const int i0, const int j0) const {
		Matrix res(rows - 1, columns - 1);
		forn(i, rows)
			if (i != i0)
				forn(j, columns)
					if (j != j0)
						res.data[i - (i >= i0)][j - (j >= j0)] = data[i][j];
		return res;
	}
	uint getDeterminant() const {
		if (rows != columns)
			return 0;
		if (rows == 1)
			return data[0][0];
		uint res = 0;
		forn(i, rows)
			res = (res + (data[i][0] * getMinor(i, 0).getDeterminant()) % MOD * (1 - 2 * (i % 2)) + MOD) % MOD;
		return res;
	}
	Matrix inverse() const {
		uint det = getDeterminant();
		if (det == 0)
			throw("Matrix is singular\n");
		uint invDet = invert(det);
		Matrix res(rows, columns);
		forn(i, rows)
			forn(j, columns)
				res.data[i][j] = ((getMinor(i, j).getDeterminant() * invDet) % MOD * (1 - 2 * ((i + j) % 2)) + MOD) % MOD;
		return res.transpose();
	}
	Vector operator *(const Vector & v) const {
		if (columns != v.getSize())
			throw("Can't multiply\n");
		Vector res(rows);
		forn(i, rows)
			res[i] = data[i].dotProduct(v);
		return res;
	}
};
