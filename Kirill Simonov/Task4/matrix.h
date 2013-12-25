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
#include <iomanip>
#include "vector.h"

using namespace std;


class Matrix {
	private:
	int ** data;
	int rows, columns;
	static const int MOD = 251;
	public:
	void del() {
		for (int i = 0; i < rows; ++i) {
			delete[] data[i];
		}
		delete[] data;
	}
	void alloc() {
		data = new int*[rows];
		for (int i = 0; i < rows; ++i) {
			data[i] = new int[columns];
		}
		clear();
	}
	Matrix& operator = (const Matrix & other) {
		del();
		columns = other.columns;
		rows = other.rows;
		alloc();
		for (int i = 0; i < rows; ++i) {
			memcpy(data[i], other.data[i], sizeof(int) * columns);
		}
		return *this;
	}
	Matrix() : data(NULL), rows(0), columns(0) {};
	Matrix(const Matrix & other) : rows(other.getRows()), columns(other.getColumns()) {
		alloc();
		for (int i = 0; i < rows; ++i) {
			memcpy(data[i], other.data[i], sizeof(int) * columns);
		}
	}
	Matrix(int _rows, int _columns) : rows(_rows), columns(_columns) {
		alloc();
	}
	/*
	Matrix(int _rows, int _columns, int val) : rows(_rows), columns(_columns) {
		alloc();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				data[i][j] = val;
			}
		}
	}*/
	Matrix(int n, int n1, int val) : rows(n), columns(n) {
		alloc();
		for (int i = 0; i < n; ++i) {
				data[i][i] = val;
		}
	}
	Matrix(Vector v) : rows(v.size()), columns(1) {
		alloc();
		for (int i = 0; i < getRows(); ++i) {
			data[i][0] = v.get(i);
		}
	}
	~Matrix() {
		del();
	}
	Matrix mod() {
		for (int i = 0; i < getRows(); ++i)
			for (int j = 0; j < getColumns(); ++j)
				data[i][j] = (data[i][j] % MOD + MOD) % MOD;
		return *this;
	}
	void clear() {
		for (int i = 0; i < rows; ++i)
			memset(data[i], 0, columns * sizeof(int));
	}
	int size() const {
		return rows * columns;
	}
	int getRows() const {
		return rows;
	}
	int getColumns() const {
		return columns;
	}
	int get(int i, int j) const{
		if (i >= rows || j >= columns) {
			throw("invalid index");
		}
		return data[i][j];
	}
	void set(int i, int j, int x) {
		if (i >= rows || j >= columns) {
			throw("invalid index");
		}
		data[i][j] = x;
	}
	Matrix transpose() const {
		Matrix w(getColumns(), getRows());
		for (int i = 0; i < w.getRows(); ++i) {
			for (int j = 0; j < w.getColumns(); ++j) {
				w.set(i, j, get(j, i));
			}
		}
		return w;
	}
	Matrix operator + (const Matrix & other) const {
		if (getRows() != other.getRows() || getColumns() != other.getColumns()) {
			throw("operator +: nonconformant arguments");
		}
		Matrix w(getRows(), getColumns());
		for (int i = 0; i < getRows(); ++i) {
			for (int j = 0; j < getColumns(); ++j) {
				w.set(i, j, get(i, j) + other.get(i, j));
			}
		}
		w.mod();
		return w;
	}
	Matrix& operator += (const Matrix & other) {
		if (getRows() != other.getRows() || getColumns() != other.getColumns()) {
			throw("operator +=: nonconformant arguments");
		}
		for (int i = 0; i < getRows(); ++i) {
			for (int j = 0; j < getColumns(); ++j) {
				set(i, j, get(i, j) + other.get(i, j));
			}
		}
		this->mod();
		return *this;
	}
	Matrix operator * (int d) const {
		Matrix w = *this;
		for (int i = 0; i < getRows(); ++i) {
			for (int j = 0; j < getColumns(); ++j) {
				w.set(i, j, get(i, j) * d);
			}
		}
		w.mod();
		return w;
	}
	Matrix operator * (const Matrix & other) const{
		if (getColumns() != other.getRows()) {
			throw("operator *: nonconformant arguments");
		}
		Matrix w(getRows(), other.getColumns());
		for (int i = 0; i < w.getRows(); ++i) {
			for (int j = 0; j < w.getColumns(); ++j) {
				int sum = 0;
				for (int k = 0; k < getColumns(); ++k) {
					sum += get(i, k) * other.get(k, j);
				}
				w.set(i, j, sum);
			}
		}
		w.mod();
		return w;
	}

	Vector operator * (const Vector & v) const{
		Matrix w(v);
		Matrix res =  ((*this) * w).mod();
		Vector ans(res.getRows());
		for (int i = 0; i < ans.size(); ++i) {
			ans.set(i, res.get(i, 0));
		}
		return ans;
	}
	bool operator == (const Matrix & other) const {
		if (getRows() != other.getRows() || getColumns() != other.getColumns()) {
			return false;
		}
		for (int i = 0; i < getRows(); ++i) {
			for (int j = 0; j < getColumns(); ++j) {
				if (get(i, j) % MOD != other.get(i, j) % MOD)
					return false;
			}
		}
		return true;
	}
	void read() {
		cin >> rows;
		cin >> columns;
		alloc();
		for (int i = 0; i < getRows(); ++i) {
			for (int j = 0; j < getColumns(); ++j) {
				cin >> data[i][j];
			}
		}
		this->mod();
	}
	void print() {
		//cout << "Matrix " << getRows() << "x" << getColumns() << ":\n";
		cout << getRows() << ' ' << getColumns() << '\n';
		cout << fixed << setprecision(6);
		for (int i = 0; i < getRows(); ++i) {
			for (int j = 0; j < getColumns(); ++j) {
				cout << get(i, j) << ' ';
			}
			cout << "\n";
		}
		cout << endl;
	}
	void swapRows(int i, int j) {
		if (i < 0 || i >= getRows() || j < 0 || j >= getRows()) {
			throw("invalid index");
		}
		swap(data[i], data[j]);
	}
	void addRows(int i, int j, int d) {
		if (i < 0 || i >= getRows() || j < 0 || j >= getRows()) {
			throw("invalid index");
		}
		for (int k = 0; k < getColumns(); ++k) {
			data[j][k] += data[i][k] * d;
		}
	}
	void multRow(int i, int d) {
		if (i < 0 || i >= getRows()) {
			throw("invalid index");
		}
		for (int k = 0; k < getColumns(); ++k) {
			data[i][k] *= d;
		}
	}
	void swapColumns(int i, int j) {
		if (i < 0 || i >= getColumns() || j < 0 || j >= getColumns()) {
			throw("invalid index");
		}
		for (int k = 0; k < getRows(); ++k) {
			swap(data[k][i], data[k][j]);
		}
	}
	void addColumns(int i, int j, int d) {
		if (i < 0 || i >= getColumns() || j < 0 || j >= getColumns()) {
			throw("invalid index");
		}
		for (int k = 0; k < getRows(); ++k) {
			data[k][j] += data[k][i] * d;
		}
	}
	void multColumn(int i, int d) {
		if (i < 0 || i >= getColumns()) {
			throw("invalid index");
		}
		for (int k = 0; k < getRows(); ++k) {
			data[k][i] *= d;
		}
	}
	int power(int x, int p) {
		if (p == 0)
			return 1;
		if (p % 2 == 0) {
			int w = power(x, p / 2);
			return (w * w) % MOD;
		} else {
			return (power(x, p - 1) * x) % MOD;
		}
	}
	int inv(int x) {
		return power(x, MOD - 2);
	}
	int det() {
		if (getRows() != getColumns())
			return 0;
		int res = 1;
		Matrix A = (*this);
		A.mod();
		int n = getRows();
		for (int i = 0; i < n; ++i) {
			int mx = i;
			for (int j = i + 1; j < n; ++j) {
				if (abs(A.get(j, i)) > abs(A.get(mx, i))) {
					mx = j;
				}
			}
			if (A.get(mx, i) % MOD == 0)
				return 0;
			A.swapRows(mx, i);
			if (i != mx) {
				res *= -1;
			}
			res *= A.get(i, i);
			int w = inv(A.get(i, i));
			A.multRow(i, w);
			for (int j = i + 1; j < n; ++j) {
				A.addRows(i, j, -A.get(j, i));
			}
			A.mod();
		}
		return res;
	}
	Matrix inverse() {
		if (det() % MOD == 0)
			throw("non-invertible");
		Matrix A = (*this);
		A.mod();
		int n = getRows();
		Matrix E(n, n, 1);
		for (int i = 0; i < n; ++i) {
			int mx = i;
			for (int j = i + 1; j < n; ++j) {
				if (abs(A.get(j, i)) > abs(A.get(mx, i))) {
					mx = j;
				}
			}
			A.swapRows(mx, i);
			E.swapRows(mx, i);
			int w = inv(A.get(i, i));
			A.multRow(i, w);
			E.multRow(i, w);
			for (int j = 0; j < n; ++j) {
				if (i == j)
					continue;
				w = -A.get(j, i);
				A.addRows(i, j, w);
				E.addRows(i, j, w);
			}
			A.mod();
			E.mod();
		}
		return E;
	}
	void makeRand() {
		for (int i = 0; i < getRows(); ++i) 
			for (int j = 0; j < getColumns(); ++j)
				data[i][j] = rand() % MOD;
	}

};
