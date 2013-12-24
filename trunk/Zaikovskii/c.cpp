#include <iostream>
#include <windows.h>
#include <math.h>
#include <stdio.h>
 

using namespace std;


//******************    Vector   *******************



int gcd(int a, int b) {
	int c;
	while (b) {
		c = a % b;
		a = b;
		b = c;        
	}
	return abs(a);
}

int invert(int k, int m) {
	if (gcd(k, m) != 1) return 0;
	else {
		k = k % m;
		int i = k;
		while ((k * i) % m != 1) {k = (k * i) % m;} 
		return k;
	}
}



class Vector
{
private:
	int length;
	double* colon;

public:
	
	Vector(int k): length(k), colon(new double[k]) {
		for (int i = 0; i < k; i++) {
			colon[i] = 0;
		}
	}

	Vector(): length(0), colon(new double[0]) {}

	
	
	Vector(const Vector& vect) : length(vect.length), colon(new double[vect.length]) {
		for (int i = 0; i < vect.length; i++) {
			colon[i] = vect.colon[i];
		}
	}


        ~Vector() {
		delete[] colon;
	}
	
	double getValue(int i) const {
		try {
			if (i < length && i >= 0) {
				return colon[i];
			}
			else throw 1;
		}
		catch (int e) {
			if (e == 1) cout << "Index out of bound.\n";
			exit(1);
		}
	}
	
	int getSize() const {
		return length;
	}

	void add(int i, double x) {
		try {
			if (i < length) colon[i] = x;
			else throw 1;
		}
		catch (int a) {
			if (a == 1) {
				cout << "Index out of bound.\n";
				exit(1);
			}
		}
	}

	void printColon() const {
		for (int i = 0; i < length; i++) {
			cout << colon[i] << endl;
		}
	}

	void printRow() const {
		cout << "(";
		for (int i = 0; i < length - 1; i++) {
			cout << colon[i] << ", ";
		}
		if (length > 0) {cout << colon[length - 1];}
		cout << ")\n";
	}

	void printRowM(int M) const {
		cout << "(";
		for (int i = 0; i < length - 1; i++) {
			cout << (int) colon[i] % M << ", ";
		}
		if (length > 0) {cout << (int) colon[length - 1] % M;}
		cout << ")\n";
	}

	void resize(int k) {
		colon = (double*) realloc(colon, k * sizeof(double));
		for (int i = length; i < k; i++) {colon[i] = 0;}
		length = k;
	}


	const Vector& operator=(const Vector& right) {
		if (this == &right) {
			return *this;
		}
		length = right.length;
		colon = (double*) realloc (colon, length * sizeof(double));
		for (int i = 0; i < length; i++) {
			colon[i] = right.colon[i];
		}
		return *this;
	}



	double& operator[](int i) {
		try{
			if (i < length) return colon[i];
			else throw 1;
		}
		catch (int a) {
			if (a == 1) {
				cout << "Index out of bound.\n";
				exit(1);
			}
		}
	}
	

	const void operator+=(const Vector& right) {
		if (length < right.length) {
			colon = (double*) realloc (colon, right.length * sizeof(double));
			for (int i = 0; i < length; i++) {
				colon[i] += right.colon[i];
			}
			for (int i = length; i < right.length; i++) {
				colon[i] = right.colon[i];
			}
			length = right.length;
		}
		else {
			for (int i = 0; i < right.length; i++) {
				colon[i] += right.colon[i];
			}
		}
		
	}

	
	const Vector operator-() const {
		Vector v = Vector(length);
		for (int i = 0; i < length; i++) {
			v.colon[i] = -colon[i];
		}
		return v;
	}

	const void operator-=(const Vector& right) {
			if (length < right.length) {
			colon = (double*) realloc (colon, right.length * sizeof(double));
			for (int i = 0; i < length; i++) {
				colon[i] -= right.colon[i];
			}
			for (int i = length; i < right.length; i++) {
				colon[i] = right.colon[i];
			}
			length = right.length;
		}
		else {
			for (int i = 0; i < right.length; i++) {
				colon[i] -= right.colon[i];
			}
		}
		
	}

	friend bool operator==(const Vector& left, const Vector& right) {
		int n = min (left.length, right.length);
		int m = max (left.length, right.length);
		for (int i = 0; i < n; i++) {
			if (left.colon[i] != right.colon[i]) return false;
		}
		if (left.length < m) {
			for (int i = n; i < m; i++) {
				if (right.colon[i] != 0) return false;
			}
		}
		else {
			for (int i = n; i < m; i++) {
				if (left.colon[i] != 0) return false;
			}
		}
		return true;
	}
	 

	friend const Vector operator+(const Vector& left, const Vector& right) {
		int size = max (left.length, right.length);
		int n = min (left.length, right.length);
		Vector sum = Vector(size);
		for (int i = 0; i < n; i++) {
			sum.colon[i] = left.colon[i] + right.colon[i];
		}
		if (left.length < size) {
			for (int i = n; i < size; i++) {
				sum.colon[i] = right.colon[i];
			}
		}
		else {
			for (int i = n; i < size; i++) {
				sum.colon[i] = left.colon[i];
			}
		}
		return Vector(sum);
		
	}

	friend const Vector operator-(const Vector& left, const Vector& right) {
		Vector diff = -(right);
		diff += left;
		return diff;
	}

	friend const double operator*(const Vector& left, const Vector& right) {
		int n = min (left.length, right.length);
		//Vector prod = Vector(1);
		double d = 0;
		for (int i = 0; i < n; i++) {
			d += left.colon[i] * right.colon[i];
		}
		//prod.colon[0] = d;
		return d;
		
	}

	const Vector operator*(double d) const {
		Vector v = Vector(length);
		for (int i = 0; i < length; i++) {
			v.colon[i] = d*colon[i];
		}
		return v;
	}

};







//*******************   Matrix   ******************************


class Matrix {

private:
	int height;
	int width;
	Vector* rows;

public:
	Matrix(int m, int n): height(m), width(n), rows(new Vector[m]){
		for (int i = 0; i < m; i++) {
			rows[i] = Vector(n);
		}
	}

	Matrix(): height(0), width(0), rows(new Vector[0]) {}

	
	
	Matrix(const Matrix& a) : height(a.height), width(a.width), rows(new Vector[height]) {
		for (int i = 0; i < height; i++) {
			rows[i] = Vector(a.rows[i]);
		}
	}


        ~Matrix() {
		delete[] rows;
	}

	int getSize() {return height*width;}

	int getHeight() {return height;}

	int getWidth() {return width;}


	const Matrix& operator=(const Matrix& right) {
		if (this == &right) {
			return *this;
		}
		width = right.width;
		height = right.height;
		delete[] rows;
		rows = new Vector[height];
		for (int i = 0; i < height; i++) {
			rows[i] = right.rows[i];
		}
		return *this;
	}



	Vector& operator[](int i) const {
		try{
			if (i < height) return rows[i];
			else throw 1;
		}
		catch (int a) {
			if (a == 1) {
				cout << "Index out of bound.\n";
				exit(1);
			}
		}
	}


	const Matrix transpose () const {
		Matrix m = Matrix(width, height);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				m[i][j] = rows[j][i];
			}
		}
		return m;
	}


	void print() const {
		for (int i = 0; i < height; i++) {
			rows[i].printRow();
			//cout << endl;
		}
		cout << endl;
	}

	const Matrix operator*(double d) const {
		Matrix a = Matrix(height, width);
		for (int i = 0; i < height; i++) {
			a.rows[i] = rows[i]*d;
		}
		return a;
	}

	void switchRows(int i, int j) {
		if (i != j) {
			Vector v = rows[i];
			rows[i] = rows[j];
			rows[j] = v;
		}
	}

	void multRow(int i, double d) {
		rows[i] = rows[i]*d;
	}

	void addRow(int i, int j, double d) {
		if (i != j) rows[i] += rows[j]*d;
	}


	friend void reduce (Matrix& a, int k) {
	        int j = k;
		while (j < a.height && a.rows[j][k] == 0) j++;
		if (j < a.height) {
			double d = a.rows[j][k]; 
			for (int i = j+1; i < a.height; i++) {
				if (a.rows[i][k] != 0 && i != j) {a.addRow(i, j, - a.rows[i][k]/d);}// a.print();
			}
			a.switchRows(j, k);
			if (j != k) {a[k] = a[k]*(-1);}// a.print();
		}
	}

	friend double det(Matrix a) {
		if (a.height != a.width) {return 0;}
		Matrix m = Matrix(a);
		//m.print();
		for (int i = 0; i < a.width; i++) {reduce(m, i);}
		double d = 1;
		for (int i = 0; i < a.width; i++) {d = d*m[i][i];}
		return d;
	}


	



	friend const Matrix operator*(const Matrix& left, const Matrix& right) {
		if (left.width != right.height) {cout << "Incorrect argument. Size mismatch.\n"; exit(1);} 
		Matrix prod = Matrix(left.width, right.height);
		Matrix m = right.transpose();
		for (int i = 0; i < left.height; i++) {
			for (int j = 0; j < right.width; j++) {
				prod[i][j] = left[i] * m[j];
			}
		}
		//roundM(prod);
                return prod;
	}

	friend Matrix roundM (Matrix& a, int M) {
		for (int i = 0; i < a.height; i++) {
			for (int j = 0; j < a.width; j++) {
				a[i][j] = (int) a[i][j] % M;
			}
		}
		return a;
	}

        friend const Vector operator*(const Matrix& left, const Vector& right) {
		if (left.width != right.getSize()) {cout << "Incorrect argument. Size mismatch.\n"; exit(1);} 
		Vector prod = Vector(left.height);
		//Matrix m = right.transpose();
		for (int i = 0; i < left.height; i++) {
			prod[i] = left[i] * right;
		}
                return prod;
	}
	


	friend Matrix inverse(Matrix a) {
		if (a.height != a.width) {cout << "Incorrect argument. The matrix is non-square."; exit(1);}
		Matrix m = Matrix(a);
		Matrix inv = Matrix(a.height, a.width);
		for (int i = 0; i < a.height; i++) {inv[i][i] = 1;}
		for (int i = 0; i < a.width; i++) {
			int j = i;
			while (j < a.height && m.rows[j][i] == 0) {j++;}
			if (j == a.height) {cout << "Incorrect argument. The matrix is degenerate."; exit(1);}
			inv.switchRows(j, i);
			m.switchRows(j, i); m.print();
			inv.multRow(i, 1/m[i][i]);
			m.multRow(i, 1/m[i][i]); m.print();
			for (int k = i + 1; k < a.width; k++) {
				inv.addRow(k, i, -m[k][i]);
				m.addRow(k, i, -m[k][i]); m.print();
			}
		}
		for (int i = a.width - 1; i >= 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				inv.addRow(j, i, -m[j][i]);
				m.addRow(j, i, -m[j][i]); m.print();
			}
		}
		//inv.print();
		//roundM(inv);
		//inv.print();
		return inv;
	}

	friend int detM(Matrix a, int m, int n) {
		if (a.height != a.width) {cout << "Incorrect argument. The matrix is non-square."; exit(1);}
		for (int i = 0; i < a.width; i ++) {
			a[i][n] = 0;
			a[m][i] = 0;
		}
		if ((m + n) % 2 == 0) a[m][n] = 1;
		else a[m][n] = 1;
		//a.print();
		return (int) det(a);
	}


	friend Matrix inverseM(Matrix a, int M) {
		if (a.height != a.width) {cout << "Incorrect argument. The matrix is non-square."; exit(1);}
		int d = invert ((int) det(a), M); //a.print(); cout << (int) det (a)%52 <<", "<< d << endl;
		Matrix inv = Matrix(a.height, a.width);
		for (int i = 0; i < a.width; i++) {
			for (int j = 0; j < a.width; j++) {
				inv[i][j] = d * detM(a, i, j) % M;
			}
		}
		inv = inv.transpose();
		//inv.print();
		return inv;
	}
	
};




//***************************   Hill cipher   ******************************

bool isLetter(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}



int encode(char c) {
	if ('a' <= c && c <= 'z') {return c - 71;}
	if ('A' <= c && c <= 'Z') {return c - 65;}
}

char decode(int i) {
	if (i < 0) i = i + 52;
	if (i < 26) return (char) (65 + i);
	if (25 < i) return (char) (i + 71);
}

char* encrypt (char* s, Matrix m) {
	int n = strlen(s);
	char* buff = new char[n + 1];
	buff[n] = '\0';
	for (int i = 0; i < n;) {
		int j = 0;
		Vector v = Vector(3);
		while (j < 3 && i < n) {
			if (isLetter(s[i])) {v[j] = encode(s[i]); i++; j++;}
			else {buff[i] = s[i]; i++; break;}
		}
		if (j == 3) {
			//v.printRow();
			v = m * v; //v.printRowM(52);
			while (j > 0) {buff[i - j] = decode(((int) v[3 - j]) % 52); j--;}
		}
		else while (j > 0) {buff[i - j - 1] = s[i - j - 1]; j--;}
	}
	return buff;
	
}


int main() 
{
	//Vector vect1 = Vector(3);
	//Vector vect2 = Vector(3);
	//for (int i = 0; i < 3; i++) {
	//	vect1[i]=i;
	//	vect2.add(i, 3-i);
	//}
	/*vect2.resize(7);
	vect2[6] = 6;
	Vector vect3 = vect2;
	vect3 -=  vect1;
	Vector vect4 = vect2 - vect1;
	cout << vect2[6] << endl;*/

	Matrix a = Matrix(3, 3);
	a[0][0] =  6; a[0][1] = 24; a[0][2] =  1;
	a[1][0] = 13; a[1][1] = 16; a[1][2] = 10; 
	a[2][0] = 20; a[2][1] = 17; a[2][2] = 15;
/*	Matrix a1 = Matrix(2, 2);
	a1[0][0] = 1;
	a1[0][1] = 1;
	a1[1][1] = 1;*/
//	a1.print();
//	(a1*a).print();
	Matrix a2 = inverseM(a, 52);
	char s[12] = {'a','c','t','a','b','c','d',' ','a','c','u','\0'};
//	cout << isLetter(s[3]) << endl;
	cout << encrypt(s, a) << endl;
	cout << encrypt(encrypt(s, a), a2)<<endl; 
//	a.print();
/*	//cout << detM(a, 1, 0) << endl;
	a2.print();
	Matrix a3 = a2*a;
	//a3.print();
	a3 = roundM(a3, 52);
	a3.print();
	a3 = a2*a;
	//a3.print();
	a3 = roundM(a3, 52);
	a3.print();
*/	//a = a.transpose();
//	cout << det(a) << endl;
//	cout << det(a2) << endl;
//	cout << det(a)*det(a2) << endl;
	//a1.print();
//	a1.resize(3, 4);
//	a1.colons[0].Print();
	return 0; 
}
