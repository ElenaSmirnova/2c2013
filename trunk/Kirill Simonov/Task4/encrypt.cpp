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

Matrix gen_key(int size) {
	Matrix key(size, size);
	do {
		key.makeRand();
	} while(key.det() == 0);
	return key;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	freopen(argv[1], "r", stdin);
	freopen((string(argv[1]) + ".enc").c_str(), "w", stdout);
	//freopen("", "w", stderr);
	int size = rand() % 10 + 10;
	Matrix key = gen_key(size);
	Vector block(size);
	int textsize = 0;
	while (!feof(stdin)) {
		int k = 0;
		while (!feof(stdin) && k < size) {
			block.set(k++, getc(stdin));
			textsize++;
		}
		for (int i = k + 1; i < size; ++i) {
			block.set(i, 0);
		}
		block.mod();
		Vector enc = key * block;
		for (int i = 0; i < size; ++i) {
			putc(enc.get(i), stdout);
		}
	}
	fclose(stdout);
	freopen("key", "w", stdout);
	cout << textsize << '\n';
	key.print();
	fclose(stdout);

	return 0;
}




