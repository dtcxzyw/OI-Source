#include <algorithm>
#include <cstdio>
const int size = 50005;
typedef unsigned int U32;
int n;
void add(U32* A, int x, U32 op) {
    while(x <= n) {
        A[x] += op;
        x += x & -x;
    }
}
U32 query(U32* A, int x) {
    U32 res = 0;
    while(x) {
        res += A[x];
        x -= x & -x;
    }
    return res;
}
U32 SA[size], SB[size];
void addImpl(int x, U32 op) {
    add(SA, x, op);
    add(SB, x, x * op);
}
U32 queryImpl(int x) {
    return (x + 1) * query(SA, x) - query(SB, x);
}
void add(int l, int r, U32 op) {
    addImpl(l, op);
    addImpl(r + 1, -op);
}
U32 query(int l, int r) {
    return queryImpl(r) - queryImpl(l - 1);
}
void clearImpl(U32* A, int x) {
    while(x <= n) {
        if(A[x])
            A[x] = 0;
        else
            break;
        x += x & -x;
    }
}
void clear(int x) {
    clearImpl(SA, x);
    clearImpl(SB, x);
}
struct Operator {
    int op, id, l, r, v;
} A[size];
int ans[size], M;
bool check(Operator& x) {
    if(x.op == 1) {
        if(x.v > M) {
            add(x.l, x.r, 1);
            return false;
        }
        return true;
    }
    U32 siz = query(x.l, x.r);
    if(siz >= x.v)
        return false;
    x.v -= siz;
    return true;
}
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    if(b == e) {
        for(int i = l; i <= r; ++i)
            ans[A[i].id] = b;
    } else {
        M = (b + e) >> 1;
        int lp = std::stable_partition(
                     A + l, A + r + 1, check) -
            A;
        for(int i = lp; i <= r; ++i)
            if(A[i].op == 1) {
                clear(A[i].l);
                clear(A[i].r + 1);
            }
        solve(l, lp - 1, b, M);
        solve(lp, r, M + 1, e);
    }
}
int main() {
    int m;
    scanf("%d%d", &n, &m);
    int ocnt = 0;
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &A[i].op, &A[i].l, &A[i].r,
              &A[i].v);
        if(A[i].op == 2)
            A[i].id = ++ocnt;
    }
    solve(1, m, 1, n);
    for(int i = 1; i <= ocnt; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
