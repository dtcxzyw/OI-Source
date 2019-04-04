#include <algorithm>
#include <cstdio>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
const int size = 200005;
struct Vec {
    int x, y;
    Vec() {}
    Vec(int x, int y) : x(x), y(y) {}
    bool operator<(const Vec& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    Vec operator-(const Vec& rhs) const {
        return Vec(x - rhs.x, y - rhs.y);
    }
} V[size];
Int64 dot(const Vec& a, const Vec& b) {
    return asInt64(a.x) * b.x + asInt64(a.y) * b.y;
}
Int64 cross(const Vec& a, const Vec& b) {
    return asInt64(a.x) * b.y - asInt64(b.x) * a.y;
}
struct Query {
    Vec v;
    Int64 ans;
    int t;
} Q[size];
struct Edge {
    int to, nxt;
} E[size * 18];
int last[size << 2], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
void insert(int l, int r, int id, int nl, int nr,
            int ref) {
    if(nl <= l && r <= nr)
        addEdge(id, ref);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(l, m, id << 1, nl, nr, ref);
        if(m < nr)
            insert(m + 1, r, id << 1 | 1, nl, nr, ref);
    }
}
int ans[size], ref[size];
Vec P[size], C[size];
Int64 query(int siz, const Vec& v) {
    int l = 1, r = siz;
    while(r - l >= 6) {
        int lp = (l * 2 + r) / 3, rp = (l + r * 2) / 3;
        if(dot(C[lp], v) < dot(C[rp], v))
            l = lp;
        else
            r = rp;
    }
    Int64 ans = 0;
    for(int i = l; i <= r; ++i)
        ans = std::max(ans, dot(C[i], v));
    return ans;
}
void solve(int l, int r, int id, int b, int e) {
    if(b > e)
        return;
    if(l != r) {
        int m = (l + r) >> 1, mid = e + 1, lp = b,
            rp = e;
        while(lp <= rp) {
            int mp = (lp + rp) >> 1;
            if(Q[mp].t > m)
                mid = mp, rp = mp - 1;
            else
                lp = mp + 1;
        }
        solve(l, m, id << 1, b, mid - 1);
        solve(m + 1, r, id << 1 | 1, mid, e);
    }
    int pcnt = 0;
    for(int i = last[id]; i; i = E[i].nxt) {
        int v = E[i].to;
        P[pcnt++] = V[v];
    }
    std::sort(P, P + pcnt);
    int top = 0;
    for(int i = 0; i < pcnt; ++i) {
        while(top >= 2 &&
              cross(C[top] - C[top - 1],
                    P[i] - C[top - 1]) >= 0)
            --top;
        C[++top] = P[i];
    }
    for(int i = b; i <= e; ++i)
        Q[i].ans =
            std::max(Q[i].ans, query(top, Q[i].v));
}
int main() {
    int n = read();
    int vcnt = 0, qcnt = 0;
    for(int i = 1; i <= n; ++i) {
        int op = read();
        switch(op) {
            case 1: {
                int id = ++vcnt;
                ref[id] = i;
                V[id].x = read();
                V[id].y = read();
            } break;
            case 2: {
                int k = read();
                insert(1, n, 1, ref[k], i, k);
                ref[k] = 0;
            } break;
            case 3: {
                int id = ++qcnt;
                Q[id].v.x = read();
                Q[id].v.y = read();
                Q[id].t = i;
            } break;
        }
    }
    for(int i = 1; i <= vcnt; ++i)
        if(ref[i])
            insert(1, n, 1, ref[i], n, i);
    solve(1, n, 1, 1, qcnt);
    for(int i = 1; i <= qcnt; ++i)
        printf("%lld\n", Q[i].ans);
    return 0;
}
