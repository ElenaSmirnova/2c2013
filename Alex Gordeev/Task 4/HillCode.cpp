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
#include "HillCode.h"

using namespace std;

typedef unsigned int uint;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

const int goodKey[3][3] = {
	{6, 24, 1},
	{13, 16, 10},
	{20, 17, 15}
};

int main() {
	Matrix key(3, 3);
	forn(i, 3)
		forn(j, 3)
			key[i][j] = goodKey[i][j];
	string s, t;
	getline(cin, s);
	t = encode(s, key);
	cout << t << '\n';
	s = decode(t, key);
	cout << s << '\n';
	return 0;
}
