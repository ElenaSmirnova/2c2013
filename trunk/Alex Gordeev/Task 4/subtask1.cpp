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

class Point {
public:
	ldb x, y;
	Point(): x(0.0L), y(0.0L) {}
	Point(ldb x, ldb y): x(x), y(y) {}
	Point operator +(const Point & p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator -(const Point & p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator *(const ldb & c) const {
		return Point(x * c, y * c);
	}
	ldb len() const {
		return sqrt(x * x + y * y);
	}
	void read() {
		cin >> x >> y;
	}
	void print(int precision = 10) const {
		cout << fixed << setprecision(precision) << "x: " << x << ",y: " << y << '\n';
	}
};

class Line {
public:
	ldb a, b, c;
	Line() : a(0), b(0), c(0) {}
	Line(const Point & p1, const Point & p2) {
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		ldb z = sqrt(a * a + b * b);
		a /= z, b /= z;
		c = -(a * p1.x - b * p1.y);
	}
	ldb distToPoint(const Point & p) const {
		return a * p.x + b * p.y + c;
	}
	void read() {
		Point p1, p2;
		p1.read(), p2.read();
		*this = Line(p1, p2);
	}
	void print(int precision = 10) const {
		cout << fixed << setprecision(precision) << a << " * x + " << b << " * y + " << c << "= 0\n";
	}
};

class Circle {
public:
	Point center;
	ldb r;
	Circle(): center(), r(0) {}
	Circle(Point circle, ldb r): center(center), r(r) {}
	vector<Point> intersectWithLine(const Line & l) const {
		vector<Point> ans;
		ldb dist = l.distToPoint(center);
		if (abs(dist) - r > EPS)
			return ans;
		Point middle = center - Point(l.a, l.b) * dist;
		if (r - abs(dist) < EPS) {
			ans.push_back(middle);
		} else {
			ldb norm_dist = sqrt(r * r - dist * dist);
			ans.push_back(middle + Point(-l.b, l.a) * norm_dist);
			ans.push_back(middle - Point(-l.b, l.a) * norm_dist);
		}
		return ans;
	}
	void read() {
		center.read();
		cin >> r;
	}
	void print(int precision = 10) const {
		cout << "center: ";
		center.print(precision);
		cout << "radius: " << fixed << setprecision(precision) << r << '\n';
	}
};

int main()
{
    Line l;
    l.read();
    Circle c;
    c.read();
    vector<Point> result = c.intersectWithLine(l);
    if (result.size() != 0) {
    	cout << "Intersections:\n";
	    forn(i, result.size())
	    	result[i].print();
	} else
		cout << "No intersections\n";
    return 0;
}
