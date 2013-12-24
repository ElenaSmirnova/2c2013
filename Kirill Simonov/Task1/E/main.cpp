#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define FOR(a, b) for (int a = 0; a < (b); ++a)
#define clr(a) memset(a, 0, sizeof(a))
#define pb(i) push_back(i)
#define sz() size()
#define forab(i, a, b) for(int i = int(a); i < int(b); ++i)
#define forn(i, n) forab(i, 0, n)
#define forba(i, b, a) for(int i = int(b) - 1; i >= int(a); --i)

typedef long long ll;
typedef long double ldb;

const ldb eps = 1e-12;

int n;
ldb x[10010];

ldb ans = -10000000.0;
int b[10010];
int bsz = 0;

int a[10010];
int sz = 0;

void upd(ldb cur) {
    if (ans - cur > eps) return;
    if (abs(ans - cur) < eps && bsz > sz) return;
    ans = cur;
    sz = bsz;
    forn(i, sz) a[i] = b[i];
}

void sol1() {
    ldb big = -10000000.0;
    int fnd = -1;
    forn(i, n)
        if (x[i] - big > eps) {
            fnd = i;
            big = x[i];
        }
    if (fnd == -1) return;
    bsz = 0;
    b[bsz++] = fnd;
    upd(big);
}

void sol2() {
    int f1 = -1, f2 = -1;
    ldb b1 = 0.0, b2 = 0.0;
    forn(i, n) {
        if (b1 - x[i] > eps) {
            f2 = f1;
            f1 = i;
            b2 = b1;
            b1 = x[i];
        } else {
            if (b2 - x[i] > eps) {
                f2 = i;
                b2 = x[i];
            }
        }
    }
    if (f1 == -1 || f2 == -1) return;
    bsz = 0;
    b[bsz++] = min(f1, f2);
    b[bsz++] = max(f1, f2);
    upd(b1 * b2);
}


void sol3() {
    int k_o = 0, k_p = 0;
    ldb big = -10000000.0, sml = 0.0;
    int bf = -1, sf = -1;
    bsz = 0;
    forn(i, n) {
        if (x[i] - 1.0 > eps) {
            k_p++;
            b[bsz++] = i;
            continue;
        }
        if (-1 - x[i] > eps) {
            k_o++;
            if (x[i] - big > eps) {
                if (bf != -1) {
                    b[bsz++] = bf;
                }
                bf = i;
                big = x[i];
            } else {
                b[bsz++] = i;
            }
            continue;
        }
        if (x[i] > -eps) continue;
        if (sml - x[i] > eps) {
            sf = i;
            sml = x[i];
        }
    }
    if (k_o != 0) {
        if (k_o % 2 == 0) {
            b[bsz++] = bf;
        } else {
            if (bf != -1 && sf != -1 && (big * sml - 1 > eps)) {
                b[bsz++] = bf;
                b[bsz++] = sf;
            }
        }
    }

    if (bsz == 0) {
        sol1();
        sol2();
        return;
    }
    sort(b, b + bsz);
    sz = bsz;
    forn(i, sz) a[i] = b[i];
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("", "w", stdout);
    cin >> n;
    forn(i, n) cin >> x[i];
    sol3();
    cout << sz << '\n';
    forn(i, sz) printf("%d ", a[i] + 1);
    printf("\n");
    return 0;
}

