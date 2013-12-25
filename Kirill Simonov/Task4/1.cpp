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
#include <vector>
#include <iomanip>

#define ll long long int
#define clr(a) memset(a, 0, sizeof(a))
#define FOR(a, b) for(int a = 0; a < (b); a++)
#define iter(a) typeof(a.begin())
#define foreach(a, it) for(typeof(a.begin()) it = a.begin(); it != a.end(); it++)

using namespace std;

const long double EPS = 1e-8;
const int INF = 1000000001;

class Point {
	public:
	double x, y;
	Point() : x(0), y(0) {};
	Point(double _x, double _y) : x(_x), y(_y) {};
	double length() const{
		return sqrt(x * x + y * y);
	}
	Point operator + (const Point & other) const {
		return *new Point(x + other.x, y + other.y);
	}
	Point operator - (const Point & other) const {
		return *new Point(x - other.x, y - other.y);
	}
	Point operator * (double c) const {
		return *new Point(x * c, y * c);
	}
	double dotProduct(const Point & other) const {
		return x * other.x + y * other.y;
	}
	double crossProduct(const Point & other) const {
		return x * other.y - y * other.x;
	}
	Point rotate90() const {
		return *new Point(y, -x);
	}
	Point norm(double l = 1.0) const {
		double cur = length();
		return * new Point(x * l / cur, y * l / cur);
	}
	void read() {
		cin >> x >> y;
	}
	void print(int precision = 6) const {
		cout << fixed << setprecision(precision) << "x: " << x << " y: " << y << '\n';
	}
};

class Line {
	public:
	Point start, dir;
	Line() : start(), dir() {};
	Line(Point s, Point d) : start(s), dir(d) {};
	double read() {
		start.read();
		dir.read();
		if (dir.length() < EPS)
			throw("zero direction vector");
	}
	double distanceTo(const Point & p) const {
		return abs((p - start).crossProduct(dir) / dir.length());
	}
	double print(int precision = 6) {
		cout << "start: \n";
		start.print(precision);
		cout << "direction: \n";
		dir.print(precision);
	}

};

class Circle {
	public:
	Point o;
	double r;
	Circle() : o(), r() {};
	Circle(Point _o, double _r) : o(_o), r(_r) {};
	double read() {
		o.read();
		cin >> r;
	}
	double print(int precision = 6) {
		cout << "centre: \n";
		o.print(precision);
		cout << "radius: " << fixed << setprecision(precision) << r << '\n';
	}
	vector<Point> intersectWith(const Line & line) const {
		vector<Point> ans;
		double dist = line.distanceTo(o);
		if (dist > r)
			return ans;
		Point v = line.dir.rotate90().norm(dist);
		Point mid = o + v;
		if (line.distanceTo(mid) > EPS)
			mid = mid - v * 2;
		double dist1 = sqrt(r * r - dist * dist);
		if (dist1 < EPS) {
			ans.push_back(mid);
		} else {
			ans.push_back(mid + line.dir.norm(dist1));
			ans.push_back(mid - line.dir.norm(dist1));
		}
		return ans;
	}
};

int main()
{
	//freopen("", "r", stdin);
	//freopen("", "w", stdout);
	//freopen("", "w", stderr);
	Line line;
	line.read();
	Circle circle;
	circle.read();
	vector<Point> res = circle.intersectWith(line);
	cout << "intersections:\n";
	FOR(i, res.size()) {
		res[i].print();
	}
	return 0;
}




