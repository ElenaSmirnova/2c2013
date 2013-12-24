#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <math.h>

using namespace std;

class Line {
	// y = ax + b
	private:
	double a, b;
	public:
	double getA() const{
		return a;}
	double getB() const{
		return b;}
	void setA(double a){
		this->a = a;}
	void setB(double b){
		this->b = b;}
	Line (double a, double b) {
		setA(a); 
		setB(b);
	}
	void print() {
		printf("y = %gx+%g\n", a, b);
	}
};

class Circle {
	// (x-cx)^2 + (y-cy)^2 = R^2
	private:
	double R;
	double cx, cy;
	public:
	double getR() const{
		return R;}
	double getCX() const{
		return cx;}
	double getCY() const{
		return cy;}
	void setR(double R){
		this->R = R;}
	void setCX(double cx){
		this->cx = cx;}
	void setCY(double cy){
		this->cy = cy;}
	Circle (double R, double cx, double cy) {
		setR(R); 
		setCX(cx);
		setCY(cy);
	}
	void print() {
		printf("(x-%g)^2 + (y-%g)^2 = %g^2\n", cx, cy , R);
	}
};

double* intersection(Line l, Circle c) {
	double A = (l.getA()*l.getA()+1);
	double B = -2*(c.getCX() - (l.getB()-c.getCY())*l.getA());
	double K = c.getCX()*c.getCX() + (l.getB() - c.getCY())*(l.getB() - c.getCY()) - c.getR()*c.getR();
	double D = B*B - 4*A*K;
	if (D < 0) {
		return 0;
	}
	D = sqrt(D);
	double x1 = (-B+D)/(2*A);
	double x2 = (-B-D)/(2*A);
	double y1 = l.getA() * x1 + l.getB();
	double y2 = l.getA() * x2 + l.getB();
	double* result = new double[4];
	result[0] = x1;
	result[1] = y1;
	result[2] = x2;
	result[3] = y2;
	return result;
};
