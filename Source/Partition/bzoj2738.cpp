#include <algorithm>
#include <cstdio>
namespace IO {
    char in[1 << 22];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
    char out[1 << 22], *S = out;
    void putc(char ch) {
        *S++ = ch;
    }
    void uninit() {
        fwrite(out, S - out, 1, stdout);
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
void print(int x) {
    if(x >= 10)
        print(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 505, maxq = 60005;
int n, S[size][size];
void add(int x, int y) {
    while(x <= n) {
        int z = y;
        while(z <= n) {
            ++S[x][z];
            z += z & -z;
        }
        x += x & -x;
    }
}
int query(int x, int y) {
    int res = 0;
    while(x) {
        int z = y;
        while(z) {
            res += S[x][z];
            z -= z & -z;
        }
        x -= x & -x;
    }
    return res;
}
void clear(int x, int y) {
    while(x <= n) {
        int z = y;
        while(z <= n) {
            if(S[x][z])
                S[x][z] = 0;
            else
                break;
            z += z & -z;
        }
        x += x & -x;
    }
}
struct Point {
    int x, y, z;
    bool operator<(const Point& rhs) const {
        return z < rhs.z;
    }
} P[size * size];
int find(int l, int r, int x) {
    int ans = 0;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(P[m].z <= x)
            l = m + 1, ans = m;
        else
            r = m - 1;
    }
    return ans;
}
struct Query {
    int x1, y1, x2, y2, k, id;
    int queryRECT() const {
        return query(x2, y2) - query(x1, y2) -
            query(x2, y1) + query(x1, y1);
    }
} Q[maxq];
int ans[maxq];
void solve(int l, int r, int pl, int pr, int ql,
           int qr) {
    if(ql > qr)
        return;
    if(l == r) {
        for(int i = ql; i <= qr; ++i)
            ans[Q[i].id] = l;
    } else {
        int m = (l + r) >> 1;
        int pm = find(pl, pr, m);
        for(int i = pl; i <= pm; ++i)
            add(P[i].x, P[i].y);
        int cur = ql;
        for(int i = ql; i <= qr; ++i) {
            int k = Q[i].queryRECT();
            if(Q[i].k > k)
                Q[i].k -= k;
            else
                std::swap(Q[cur++], Q[i]);
        }
        for(int i = pl; i <= pm; ++i)
            clear(P[i].x, P[i].y);
        solve(l, m, pl, pm, ql, cur - 1);
        solve(m + 1, r, pm + 1, pr, cur, qr);
    }
}
int X[size * size];
int main() {
    IO::init();
    n = read();
    int q = read();
    int siz = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int id = ++siz;
            P[id].x = i, P[id].y = j, P[id].z = read();
            X[id] = P[id].z;
        }
    }
    std::sort(X + 1, X + siz + 1);
    siz = std::unique(X + 1, X + siz + 1) - (X + 1);
    int tot = n * n;
    for(int i = 1; i <= tot; ++i)
        P[i].z = std::lower_bound(X + 1, X + siz + 1,
                                  P[i].z) -
            X;
    std::sort(P + 1, P + tot + 1);
    for(int i = 1; i <= q; ++i) {
        Q[i].id = i;
        Q[i].x1 = read() - 1;
        Q[i].y1 = read() - 1;
        Q[i].x2 = read();
        Q[i].y2 = read();
        Q[i].k = read();
    }
    solve(1, siz, 1, tot, 1, q);
    for(int i = 1; i <= q; ++i) {
        print(X[ans[i]]);
        IO::putc('\n');
    }
    IO::uninit();
    return 0;
}
