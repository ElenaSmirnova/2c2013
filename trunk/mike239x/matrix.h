#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

/*
Реализовать класс Matrix для хранения массива векторов.
Реализовать деструктор.
Реализовать метод, возвращающий размер матрицы.
Реализовать метод, возвращающий количество столбцов и строк.
Реализовать метод, возвращающий транспонированную матрицу.
Реализовать метод, возвращающий детерминант матрицы.
Реализовать метод, возвращающий обратную матрицу.
*/

class Matrix {
	private:
	int height, width;
	double * data;
	public:
	Matrix(){
		height = 0;
		width = 0;
		data = 0;
	}
	Matrix(int h, int w) : height(h), width(w)
	{
		data = new double[h * w];
		for (int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++) {
				data[i * width + j] = 0;
			}
		}
	}
	Matrix(const Matrix & toCopy) {
		height = toCopy.getHeight();
		width = toCopy.getWidth();
		data = new double[height * width];
		for (int i = 0; i < height * width; i++) {
			data[i] = toCopy.get(i);
		}
	}
	double get(int globalIndex) const {
		if (globalIndex < 0 || globalIndex >= height * width) {
			cerr << "index out of bounds ecxeption!";
			return -1;
		} else {
			return data[globalIndex];
		}
	}
	double get(int x, int y) const{
		if (x < 0 || x >= width || y < 0 || y >= height) {
			cerr << "index out of bounds ecxeption!";
			return -1;
		}
		return data[y * width + x];
	}
	int getCellsNum() const{
		return height*width;
	}
	int getHeight() const{
		return height;
	}
	int getWidth() const{
		return width;
	}
	int* getSize() const{
		int* size = new int[2];
		size[0] = height;
		size[1] = width;
		return size;
	}
	void set(int x, int y, double val) {
		if (x < 0 || x >= width || y < 0 || y >= height) {
			cerr << "index out of bounds ecxeption: " << x << ", " << y << endl;
		}
		data[y * width + x] = val;
	}
	void setGlobaly(int globalIndex, double val) {
		if (globalIndex < 0 || globalIndex >= width*height) {
			cerr << "global index out of bounds ecxeption!" << endl;
		}
		data[globalIndex] = val;
	}
	Matrix transpose() const{
		Matrix tr = Matrix(width, height);
		for (int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				tr.set(y, x, get(x, y));
			}
		}
		return tr;
	}
	void operator= (const Matrix& m) {
		height = m.getHeight();
		width = m.getWidth();
		data = new double[height * width];
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++){
				data[i*width + j] = m.get(j,i);
			}
		}
	}

	double determinant() const{
		if (height != width) {
			return 0;
		}
		bool* fl = new bool[width];
		for (int i = 0; i < width; i++) {
			fl[i]=1;
		}
		return det(fl, 0, 0, -1, -1);
	}

    Matrix adjugate() const{
		if (width!=height){
            Matrix re = Matrix();
			return re;
		}
		Matrix result = Matrix(width, height);
		bool* fl = new bool[width];
		for (int i = 0; i < width; i++) {
			fl[i]=1;
		}
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				result.set(x, y, det(fl, 0, 1, y, x));
			}
		}
		result = result.transpose();
		return result;
	}

	Matrix inverse() const{
		if (width!=height){
            Matrix re = Matrix();
			return re;
		}
		double d = determinant();
		if (d == 0) {
		    Matrix re = Matrix();
			return re;
		}
		Matrix result = Matrix(width, height);
		bool* fl = new bool[width];
		for (int i = 0; i < width; i++) {
			fl[i]=1;
		}
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				result.set(x, y, det(fl, 0, 1, y, x)/d);
			}
		}
		result = result.transpose();
		return result;
	}

	double det(bool* flags, int line, bool cond, int cond_line, int cond_column) const{
		//code this recursivly
		int cnt = 0;
		double sum = 0;
		if (line >= height) {
			return 1;
		}
		if (cond_line==line) {
			//cond
			for (int x = 0; x < width; x++) {
				if (flags[x]) {
					if (cond_column==x){
						flags[x]=0;
						double re = det(flags, line+1, cond, cond_line, cond_column);
						flags[x] = 1;
						if (cnt%2) {
							re*=-1;
						}
						return re;
					}
					cnt++;
				}
			}
		} else {
			for (int x = 0; x < width; x++) {
				if (flags[x]) {
					flags[x]=0;
					double re = det(flags, line+1, cond, cond_line, cond_column);
					flags[x] = 1;
					if (cnt%2) {
						re*=-1;
					}
					re*=get(x,line);
					sum+=re;
					cnt++;
				}
			}
			return sum;
		}
		return sum;
	}

    Matrix multiply( Matrix toMul ) const {
        if (width != toMul.getHeight()) {
            Matrix re = Matrix();
			return re;
        }
        Matrix re = Matrix(height, toMul.getWidth());
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < toMul.getWidth(); x++) {
                double toWrite = 0;
                for (int index = 0; index < width; index++) {
                    toWrite+=get(index,y)*toMul.get(x,index);
                }
                re.set(x,y,toWrite);
            }
        }
        return re;
    }

	void print() {
		for (int y = 0; y < height; y ++) {
			for (int x = 0; x < width; x ++) {
				cout << get(x, y) << " ";
			}
			cout << endl;
		}
	}
/*
Реализовать метод, возвращающий детерминант матрицы.
Реализовать метод, возвращающий обратную матрицу.
*/
	~Matrix() {
		delete [] data;
	}
};

