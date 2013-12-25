#include <iostream>
#include <cmath>
using namespace std;

class Line {
public:
	float a;
	float b;
	void set_a (float sa) {
		a = sa;
	}
	float get_a () {
		return a;
	}

	void set_b (float sb) {
		b = sb;
	}

	float get_b () {
		return b;
	}

	void print () {
		cout << "a = " << a << ", b = " << b << "\n";
	}
};

class Circle {
public:
	float x;
	float y;
	float r;

	void set_x (float sx) {
		x = sx;
	}

	float get_x () {
		return x;
	}

	void set_y (float sy) {
		y = sy;
	}

	float get_y () {
		return y;
	}

	void set_r (float sr) {
		r = sr;
	}

	float get_r () {
		return r;
	}

	void print () {
		cout << "x = " << x << ", y = " << y << ", R = " << r <<"\n";
	}
};

void Solve (Line line, Circle circle){
	float a, b, r, x, y;
    float c1, c2, D;
	
	a = line.get_a ();
    b = line.get_b ();

    x = circle.get_x ();
    y = circle.get_y ();
    r = circle.get_r ();

    D = (((x + a / b * b - (y * a) / b)) * (x + a / b * b - (y * a) / b) - (1 + a * a / (b * b)) * (x * x + (1 / b - y) * (1 / b - y) - r * r));

    if (D < 0) {
		cout << "There aren't real roots.";
    } else {
		c1 = (x + (1 / b - y) * a / b + sqrt (D)) / (1 + a * a / (b * b));
		c2 = (x + (1 / b - y) * a / b - sqrt (D)) / (1 + a * a / (b * b));
		cout << "c1 = " << c1 << ",  c2 = " << c2 << "\n";
    };
};

int main () {
    float a, b, x ,y, r;

    cout << "Print a and b: \n";

    cin >> a; cin >> b;

    cout << "Print x, y and r: \n";

    cin >> x;
    cin >> y;
    cin >> r;

    class Line line;
    line.set_a (a);
    line.set_b (b);

    line.print ();

    class Circle circle;
    circle.set_r (r);
    circle.set_x (x);
    circle.set_y (y);

    circle.print ();

    Solve (line,circle);
	
	cin >> r;
    return 0;
}