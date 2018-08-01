#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
const int end = 50000, size = end + 5, mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int neg(int x) {
    return x ? mod - x : 0;
}
struct Value {
    int cnt, sum;
    Value() {}
    Value(int cnt, int sum) : cnt(cnt), sum(sum) {}
    Value operator+(const Value rhs) const {
        return Value(cnt + rhs.cnt, add(sum, rhs.sum));
    }
    Value operator-(const Value rhs) const {
        return Value(cnt - rhs.cnt, sub(sum, rhs.sum));
    }
};
struct Node {
    int ls, rs;
    Value val;
} T[size * 200];
int icnt = 0, root[size] = {};
Value queryImpl(int l, int r, int rt, int nl, int nr) {
    if (rt) {
        if (nl <= l && r <= nr)
            return T[rt].val;
        else {
            int m = (l + r) >> 1;
            Value res(0, 0);
            if (nl <= m) res = res + queryImpl(l, m, T[rt].ls, nl, nr);
            if (m < nr) res = res + queryImpl(m + 1, r, T[rt].rs, nl, nr);
            return res;
        }
    }
    return Value(0, 0);
}
Value query(int x, int kl, int kr) {
    Value res(0, 0);
    while (x) {
        res = res + queryImpl(1, end, root[x], kl, kr);
        x -= x & -x;
    }
    return res;
}
Value query(int l, int r, int kl, int kr) {
    if (l <= r && kl <= kr) return query(r, kl, kr) - query(l - 1, kl, kr);
    return Value(0, 0);
}
void modifyImpl(int l, int r, int &rt, int p, Value val) {
    if (!rt) rt = ++icnt;
    T[rt].val = T[rt].val + val;
    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m)
            modifyImpl(l, m, T[rt].ls, p, val);
        else
            modifyImpl(m + 1, r, T[rt].rs, p, val);
    }
}
void modify(int x, int siz, int p, Value val) {
    while (x <= siz) {
        modifyImpl(1, end, root[x], p, val);
        x += x & -x;
    }
}
int A[size], w[size];
int main() {
    int n = read();
    int m = read();
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        A[i] = read();
        w[i] = read();
        long long cw = w[i];
        Value cur = query(1, n, A[i] + 1, end);
        res = add(res, (cur.cnt * cw + cur.sum) % mod);
        modify(i, n, A[i], Value(1, w[i]));
    }
    for (int i = 1; i <= m; ++i) {
        int u = read();
        int v = read();
        if (u != v) {
            if (u > v) std::swap(u, v);
            int l = u + 1, r = v - 1;
            {
                long long uw = w[u];
                Value c1 = query(l, r, A[u] + 1, end);
                res = add(res, (c1.cnt * uw + c1.sum) % mod);
                Value c2 = query(l, r, 1, A[u] - 1);
                res = sub(res, (c2.cnt * uw + c2.sum) % mod);
            }
            {
                long long vw = w[v];
                Value c1 = query(l, r, 1, A[v] - 1);
                res = add(res, (c1.cnt * vw + c1.sum) % mod);
                Value c2 = query(l, r, A[v] + 1, end);
                res = sub(res, (c2.cnt * vw + c2.sum) % mod);
            }
            if (A[u] > A[v])
                res = sub(res, w[u] + w[v]);
            else if (A[u] < A[v])
                res = add(res, w[u] + w[v]);
            modify(u, n, A[u], Value(-1, neg(w[u])));
            modify(v, n, A[v], Value(-1, neg(w[v])));
            std::swap(A[u], A[v]);
            std::swap(w[u], w[v]);
            modify(u, n, A[u], Value(1, w[u]));
            modify(v, n, A[v], Value(1, w[v]));
        }
        printf("%d\n", res);
    }
    return 0;
}
