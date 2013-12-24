#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstring>

using namespace std;

#define FOR(a, b) for (int a = 0; a < (b); ++a)
#define clr(a) memset(a, 0, sizeof(a))

typedef long long ll;
typedef long double ldb;

const ldb EPS = 1e-8;

struct pond {
    int max;
    double cur;
    int in;
    int n;
};

bool operator < (pond a, pond b)
{
    if (a.in != b.in) return a.in < b.in;
    return a.n < b.n;
}

const int MAXN = 100001;
pond a[MAXN];
vector<int> e[MAXN];
int q[MAXN];

int main()
{
    //freopen("a.in", "r", stdin);
    //freopen("", "w", stdout);
    int n, k;
    cin >> n >> k;
    FOR(i, n) {
        int w;
        scanf("%d%d", &a[i].max, &w);
        a[i].cur = w;
        a[i].n = i;
        a[i].in = 0;
    }
    FOR(i, k) {
        int f, t;
        scanf("%d%d", &f, &t);
        f--;
        t--;
        a[t].in++;
        e[f].push_back(t);
    }
    int st, add, en;
    cin >> st >> add >> en;
    st--;
    en--;
    a[st].cur += add;
    set<pond> q;
    q.insert(a[st]);
    while (q.size() > 0) {
        pond cur = *q.begin();
        q.erase(cur);
        double w = (cur.cur - (double)cur.max);
        w  /= (double)(e[cur.n].size());
        if (w < -EPS)
            w = 0;
        FOR(i, e[cur.n].size()) {
            if (q.count(a[e[cur.n][i]]) > 0)
                q.erase(a[e[cur.n][i]]);
            a[e[cur.n][i]].cur += w;
            a[e[cur.n][i]].in--;
            q.insert(a[e[cur.n][i]]);
        }
    }
    printf("%.6lf", min(a[en].cur, (double)a[en].max));
    return 0;
}

