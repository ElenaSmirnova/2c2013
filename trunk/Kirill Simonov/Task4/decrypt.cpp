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
#include "matrix.h"

#define ll long long int
#define clr(a) memset(a, 0, sizeof(a))
#define FOR(a, b) for(int a = 0; a < (b); a++)
#define iter(a) typeof(a.begin())
#define foreach(a, it) for(typeof(a.begin()) it = a.begin(); it != a.end(); it++)

using namespace std;

const long double EPS = 1e-8;
const int INF = 1000000001;

int main(int argc, char * argv[])
{
	freopen(argv[1], "r", stdin);
	int textsize;
	cin >> textsize;
	Matrix key;
	key.read();
	freopen(argv[2], "r", stdin);

	freopen((string(argv[2]) + ".dec").c_str(), "w", stdout);
	int size = key.getRows();
	Matrix kinv = key.inverse();
	Vector block(size);
	
	while (!feof(stdin)) {
		int k = 0;
		while (!feof(stdin) && k < size) {
			block.set(k++, getc(stdin));
		}
		for (int i = k + 1; i < size; ++i) {
			block.set(i, 0);
		}
		block.mod();
		Vector dec = kinv * block;
		for (int i = 0; i < size; ++i) {
			if (--textsize <= 0)
				break;
			putc(dec.get(i), stdout);
		}
		if (textsize <= 0)
			break;
	}
	return 0;
}




