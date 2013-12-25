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
#include "matrix.h"

using namespace std;

typedef unsigned int uint;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

string apply(string s, Matrix key) {
	int k = key.getColumns();
	while (s.length() % k != 0)
		s += ' ';
	string res = "";
	for(int i = 0; i < s.length(); i += k) {
		Vector v(k);
		forn(j, k) 
			v[j] = (unsigned char)s[i + j];
		v = key * v;
		forn(j, k)
			res += v[j];
	}
	return res;
}

string encode(string s, Matrix key) {
	return apply(s, key);
}

string decode(string s, Matrix key) {
	return apply(s, key.inverse());
}
