#include <algorithm>
#include <cstdio>
const int size = 60005, delta = 100005;
int S[delta * 4], off, ssiz;
void add(int x) {
    x += off;
    if(x <= 0)
        return;
    while(x <= ssiz) {
        ++S[x];
        x += x & -x;
    }
}
void clear(int x) {
    x += off;
    if(x <= 0)
        return;
    while(x <= ssiz) {
        if(S[x])
            S[x] = 0;
        else
            break;
        x += x & -x;
    }
}
int query(int x) {
    x += off;
    if(x < 0)
        throw;
    int res = 0;
    while(x) {
        res += S[x];
        x -= x & -x;
    }
    return res;
}
struct Operator {
    int op, x, y, z, id;
    bool operator<(const Operator& rhs) const {
        return x < rhs.x;
    }
} A[size * 4];
int V[size], ans[size * 2];
void solve(int l, int r) {
    if(l >= r)
        return;
    int m = (l + r) >> 1;
    solve(l, m);
    solve(m + 1, r);
    for(int i = m + 1, j = l; i <= r; ++i) {
        while(j <= m && A[j].x <= A[i].x) {
            if(A[j].op == 0)
                add(A[j].y);
            ++j;
        }
        if(A[i].op) {
            int cnt = query(A[i].z) - query(A[i].y),
                id = A[i].id;
            if(A[i].op == 1)
                ans[id] -= cnt;
            else
                ans[id] += cnt;
        }
    }
    for(int i = l; i <= m; ++i)
        if(A[i].op == 0)
            clear(A[i].y);
    std::inplace_merge(A + l, A + m + 1, A + r + 1);
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) {
        A[i].op = 0;
        scanf("%d", &V[i]);
        A[i].x = i + V[i], A[i].y = i - V[i];
    }
    char op[10];
    int ocnt = 0, siz = n, minz = 1 << 30,
        maxz = -minz;
    for(int i = 1; i <= q; ++i) {
        int x, k;
        scanf("%s%d%d", op, &x, &k);
        if(op[0] == 'M') {
            int id = ++siz;
            A[id].op = 0;
            A[id].x = x + k;
            A[id].y = x - k;
            V[x] = k;
        } else {
            int px = x + V[x], py = x - V[x],
                y = py - k - 1, z = py + k;
            minz = std::min(minz, y);
            maxz = std::max(maxz, z);
            int id = ++siz, out = ++ocnt;
            A[id].op = 1;
            A[id].x = px - k - 1;
            A[id].y = y, A[id].z = z;
            A[id].id = out;
            id = ++siz;
            A[id].op = 2;
            A[id].x = px + k;
            A[id].y = y, A[id].z = z;
            A[id].id = out;
        }
    }
    off = 1 - minz, ssiz = maxz - minz + 1;
    solve(1, siz);
    for(int i = 1; i <= ocnt; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
