#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

/*Реализовать класс Vector для хранения массива вещественных чисел. 
В случае некорректного аргумента или индекса выбрасывать соответствующие исключения. 
Индексация элементов с 0. 
Реализовать конструктор с резервированием памяти, инициализированный 0.
Реализовать конструктор копии. 
Реализовать деструктор. 
Реализовать метод, возвращающий размер вектора.

Перегрузить операторы ,==,+=,+,-,умножение,\.
В случае операций над векторами разной размерности, меньший вектор расширять до размера большего добавляя 0.*/

class Vector {

	private:
	int size;
	double * data;
	public:
	Vector(){
		size = 0;
		data = 0;
	}
	Vector (int Size){
		size = Size;
		data = new double[size];
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}
	Vector(const Vector & toCopy) {
		size = toCopy.getSize();
		data = new double[size];
		for (int i = 0; i < size; i++) {
			data[i] = toCopy.get(i);
		}
	}
	int getSize() const{
		return size;
	}
	double * getData() const {
		return data;
	}
	double get(int index) const{
		if (index < 0 || index >= size) {
			cerr << "got bad array index!\n";
			return -1;
		}
		return data[index];
	}
	void set(int index, double val) {
		if (index < 0 || index >= size) {
			cerr << "got bad array index!\n";
		} else {
			data[index] = val;
		}
	}
	void print() {
		printf("instance of class vector, size of %d\n", size);
		printf("{\n");
		for (int i = 0; i < size; i++) {
			printf("%g\n", get(i));
		}
		printf("}\n\n");
	}
	void operator= (const Vector& v) {
		size = v.getSize();
		data = new double[size];
		for (int i = 0; i < size; i++) {
			data[i] = v.get(i);
		}
	}
	bool operator== (const Vector& v) const{
		if (getSize()!=v.getSize()) {
			return 0;
		}
		for (int i = 0; i < size; i++) {
			if (get(i) != v.get(i)) {
				return 0;
			}
		}
		return 1;
	}
	void operator+= (const Vector& toAdd){
		int maxSize = max(getSize(), toAdd.getSize());
		double * copyData = data;
		data = new double[maxSize];
		for (int i = 0; i < maxSize; i++) {
			data[i] = 0;
		}
		for (int i = 0; i < size; i++) {
			data[i] = copyData[i];
		}
		size = toAdd.getSize();
		for (int i =0; i < size; i++) {
			data[i]+=toAdd.get(i);
		}
		size = maxSize;
	}
	Vector operator+ (const Vector& toAdd) const{
		Vector temple = toAdd;
		temple += *this;
		return temple;
	}
	void operator-= (const Vector& toSub){
		int maxSize = max(getSize(), toSub.getSize());
		double * copyData = data;
		data = new double[maxSize];
		for (int i = 0; i < maxSize; i++) {
			data[i] = 0;
		}
		for (int i = 0; i < size; i++) {
			data[i] = copyData[i];
		}
		size = toSub.getSize();
		for (int i =0; i < size; i++) {
			data[i]-=toSub.get(i);
		}
		size = maxSize;
	}
	Vector operator- (const Vector& toSub) const{
		Vector temple = toSub;
		temple -= *this;
		return temple;
	}
	void operator*= (const double a){
		for (int i = 0; i < size; i++) {
			data[i]*=a;
		}
	}
	Vector operator* (const double a) const{
		Vector temple = *this;
		temple *= a;
		return temple;
	}
	void operator/= (const double a){
		if (a == 0) {
			cerr << "division by zero!\n";
		}else{
			for (int i = 0; i < size; i++) {
				data[i]/=a;
			}
		}
	}
	Vector operator/ (const double a) const{
		Vector temple = *this;
		if (a == 0) {
			cerr << "division by zero!\n";
		}else{
			temple /= a;
		}
		return temple;
	}
	~Vector() {
		delete [] data;
	}
};
