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

typedef unsigned int uint;

#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

const uint MOD = 251;

uint myPow(const uint a, const int b) {
	if (b == 0)
		return 1;
	if (b % 2 == 0)
		return myPow((a * a) % MOD, b / 2);
	return (a * myPow(a, b - 1)) % MOD;
}

uint invert(const uint a) {
	return myPow(a, MOD - 2);
}
