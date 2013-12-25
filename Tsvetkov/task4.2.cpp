#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
#define u 1024

using namespace std;
int s[u][u];
int q[u];

class Vector {
public:
	int dim;
	int x[u];
	
	Vector (int dim, int x[u]) {
		SetVector (dim, x);
	}

	~Vector (void);

	int get_dim () {
		return dim;
	}

	void GetVector () {
		for (int i = 0; i < dim; i++) {
			printf ("%d\n", x[i]);
		}
	}

	Vector (const Vector &vec) {
		dim = vec.dim;
        for (int i = 0; i < dim; i++) {
			x[i] = vec.x[i];
		}
	}

	void SetVector (int dim_1, int x_1[u]) {
		dim = dim_1;
		for (int i = 0; i < dim; i++) {
			x[i]=x_1[i];
		}
	}

	bool operator == (Vector vec) const {
		for (int i = 0; i < dim; i++) {
            if (x[i] == vec.x[i]) {
            } else {
				return false;
			}
            return true;
		}
	}

	Vector operator + (Vector vec) const {
		for (int i = 0; i < u; i++) {
			q[i]=0;
		}
		Vector v (dim, q);
		for (int i = 0; i < dim ; i++) {
			v.x[i] = x[i] + vec.x[i];
		}
		return v;
	}

	Vector operator - (Vector vec) const {
		for (int i = 0; i < u; i++) {
			q[i]=0;
		}
		Vector v (dim, q);
		for (int i = 0; i < dim ; i++) {
			v.x[i]=x[i] - vec.x[i];
		}
		return v;
	}

	Vector operator * (int a) const {
		for (int i = 0; i < u ; i++) {
			q[i]=0;
		}

		Vector v (dim, q);
		for (int i = 0; i < dim; i++) {
			v.x[i]= a * x[i];
		}
		return v;
	}

	int operator / (Vector vec) const {
		int prd = 0;
		for (int i = 0; i < dim; i++) {
			prd += x[i]*vec.x[i];
		}
		return prd;
	}
};

class Matrix {
public:
	int length;
	int width;
	int a[u][u];

	int get_length () {
		return length;
	}

	int get_width () {
            return width;
	}


	Matrix(int length,int width,int a[u][u]) {
            SetMatrix(length,width,a);
	}

	~Matrix(void);

	Matrix (const Matrix &mat) {
		length = mat.length;
        width= mat.width;
        for (int i = 0; i < width; i++) {
			for(int j = 0; j < length; j++) {
				a[i][j]= mat.a[i][j];
			}
		}
	}

	void SetMatrix (int length_1,int width_1,int a_1[u][u]) {
		length = length_1;
		width = width_1;
		for (int i = 0; i < width; i++) {
			for(int j = 0; j < length; j++) {
				a[i][j] = a_1[i][j];
			}
		}
	}

	bool operator==(Matrix mat) const {
        for(int i = 0; i < width; i++) {
			for(int j = 0; j < length;	j++){
				if (a[i][j]==mat.a[i][j]) {
            } else {
				return false;}
			}
		}
		return true;
	}

	Matrix operator + (Matrix mat) const {
		for (int i = 0; i < u; i++) {
			for(int j = 0; j < u; j++) {
				s[i][j]=0;
			}
		}

		Matrix m (mat.length, mat.width, s);
		for(int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				m.a[i][j] = a[i][j] + mat.a[i][j];
			}
		}
		return m;
	}

	Matrix operator - (Matrix mat) const {
		for (int i = 0; i < u; i++) {
			for(int j = 0; j < u; j++) {
				s[i][j]=0;
			}
		}

		Matrix m (mat.length, mat.width, s);
		for(int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				m.a[i][j] = a[i][j] - mat.a[i][j];
			}
		}
		return m;
	}

	Matrix operator * (float c) const {
		for (int i = 0; i < u; i++) {
			for(int j = 0; j < u; j++) {
				s[i][j] = 0;
			}
		}

		Matrix mat (length, width, s);
		for(int i = 0; i < width; i++) {
			for(int j = 0; j < length; j++) {
				mat.a[i][j] = a[i][j] * c;
			}
		}
		return mat;
	}

	Vector operator * (Vector vec) const{
		for (int i = 0; i < u; i++) {
			q[i]=0;
		}
		
		Vector v (vec.dim, q);
		for (int i = 0; i < vec.dim; i++) {
			for (int j = 0; j < length; j++) {
				v.x[i] = v.x[i] + vec.x[j] * a[i][j];
			}
		}
		return v;
	}

	Matrix operator / (Matrix mat) const{
		for (int i = 0; i < u; i++) {
			for (int j = 0; j < u; j++) {
				s[i][j]=0;
			}
		}
		
		Matrix m (mat.length, width, s);
		for(int i = 0; i < m.width; i++) {
			for (int j = 0; j < m.length; j++) {
				for(int k = 0; k < length; k++)	{
					m.a[i][j] += a[i][k] * mat.a[k][j];
				}
			}
		}
		return m;
	}

	Matrix transpose () {
		for (int i = 0; i < u; i++) {
			for (int j = 0; j < u; j++) {
				s[i][j]=0;
			}
		}

		Matrix m (width, length, s);
		for(int i = 0; i < length; i++) {
			for(int j = 0; j < width; j++) {
				m.a[i][j] = a[j][i];
            }
		}
		return m;
	}

	Matrix inverse () {
		int b, c, sum = 0;
        Matrix m (length, length, s);
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j ++ ) {
             m.a[i][j] = 0;
			}
            m.a[i][i] = 1;
		}
		for (int i = 0; i < length; i ++ ) {
			b = a[i][i];
			for (int j = i + 1; j < length; j++) {
				c = a[j][i];
				for (int k = 0; k < length; k ++ ) {
					a[j][k] = a[i][k] * c - a[j][k] * b;
					m.a[j][k]= m.a[i][k] * c - m.a[j][k] * b;
				}
			}
		}
		for (int i = 0; i < length; i++) {
			for (int j = length - 1; j >= 0; j--) {
				for (int k = length - 1; k > j; k--) {
					sum += a[j][k] * m.a[k][i];
				}
                if (a[j][j] == 0) {
					for (int l = 0; l < length; l++) {
                        delete [] &m.a[l];
					}
					delete [] &m;
                }
                m.a[j][i] = (m.a[j][i] - sum ) / a[j][j];
			}
		}
	return m;
    }
};

string Hill (string key, string String)
{
    int l, h, l_1, code;
    int a[u][u];
    int x[u];
    for (int i = 0; i < u; i++) {
		for(int j = 0; j < u; j++) {
			a[i][j]=0;
		}
		x[i] = 0;
	}

    //
    h = sizeof (key);
    l = sqrt (h);

	for (int i = 0; i < l; i++) {
		for(int j = 0; j < l; j++) {
			code = key[i*l+j] - 'A';
			a[i][j]=code;
		}
	}

    //

    Matrix m (l, l, a);

    l_1 = sizeof (String);
    for(int i = 0; i < l_1; i++) {
		code=String[i] - 'A';
		x[i]=code;
	}

	Vector v_1(l, x);
	v_1 = m * v_1;

    for (int i = 0; i < l_1; i++) {
		v_1.x[i] = v_1.x[i] % 26;
		String[i] = 'A' + v_1.x[i];
	}

    return String;
}

string DeHill (string key, string String) {
	int l, h, l_1, code;
    int a[u][u];
    int x[u];
    for(int i = 0; i < u; i++) {
		for(int j = 0; j < u; j++) {
			a[i][j]=0;
		}
		x[i] = 0;
	}

    //

    h = sizeof(key);
    l = sqrt(h);

	for (int i = 0; i < l; i++) {
		for(int j = 0; j < l; j++) {
			code = key[i*l+j] - 'A';
			a[i][j]=code;
		}
	}

    //

    Matrix m (l, l, a);

    l_1 = sizeof(String);
    for (int i = 0; i < l_1; i++) {
		code = String[i] - 'A';
        x[i] = code;
	}

	Vector v_1 (l, x);
	Matrix mat (l, l, a);
    mat = mat.inverse();
	v_1 = mat * v_1;

    for (int i = 0; i < l_1; i++) {
		v_1.x[i] = v_1.x[i] % 26;
		String[i]='A' + v_1.x[i];
	}
    return String;
}


int main () {
	string string = "hello", key = "world", hString = "";
	int answer;

	if (answer == 0) {
        hString = Hill (key, string);
	} else {
		hString = DeHill (key, string);
	}

	printf ("%s\n", hString);
	cin >> answer;
}