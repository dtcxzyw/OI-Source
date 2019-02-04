#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int size = 100005;
int A[size], B[size], siz;
int find(int x) {
    return std::upper_bound(B + 1, B + siz + 1, x) -
        B - 1;
}
int C[20][size], lg2[size];
int choose(int a, int b) {
    return A[a] > A[b] ? a : b;
}
void buildST(int n) {
    for(int i = 2; i <= n; ++i)
        lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1; i <= n; ++i)
        C[0][i] = i;
    for(int i = 1; i < 20; ++i) {
        int end = n - (1 << i) + 1, off = 1 << (i - 1);
        for(int j = 1; j <= end; ++j)
            C[i][j] =
                choose(C[i - 1][j], C[i - 1][j + off]);
    }
}
int getMaxPos(int l, int r) {
    int p = lg2[r - l + 1];
    return choose(C[p][l], C[p][r - (1 << p) + 1]);
}
struct Node {
    int l, r, siz;
} T[size * 20];
int icnt = 0, root[size];
int insert(int l, int r, int src, int p) {
    int id = ++icnt;
    T[id] = T[src];
    ++T[id].siz;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, T[id].l, p);
        else
            T[id].r = insert(m + 1, r, T[id].r, p);
    }
    return id;
}
int query(int l, int r, int id, int nl, int nr) {
    if(T[id].siz == 0)
        return 0;
    if(nl <= l && r <= nr)
        return T[id].siz;
    int m = (l + r) >> 1, res = 0;
    if(nl <= m)
        res += query(l, m, T[id].l, nl, nr);
    if(m < nr)
        res += query(m + 1, r, T[id].r, nl, nr);
    return res;
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 res = 0;
int n;
void solve(int l, int r) {
    if(l > r)
        return;
    int mp = getMaxPos(l, r), val = A[mp];
    int ll = l, lr = mp, rl = mp, rr = r;
    if(lr - ll > rr - rl) {
        std::swap(ll, rl);
        std::swap(lr, rr);
    }
    for(int i = ll; i <= lr; ++i) {
        int vi = A[i], rt = root[find(val / vi)];
        res += query(1, n, rt, rl, rr);
    }
    solve(l, mp - 1);
    solve(mp + 1, r);
}
int ord[size];
bool cmp(int a, int b) {
    return A[a] < A[b];
}
int main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i)
        ord[i] = i;
    std::sort(ord + 1, ord + n + 1, cmp);
    siz = 0;
    for(int i = 1; i <= n; ++i) {
        int cp = ord[i];
        int cval = A[cp];
        if(cval != B[siz]) {
            B[++siz] = cval;
            root[siz] = root[siz - 1];
        }
        root[siz] = insert(1, n, root[siz], cp);
    }
    buildST(n);
    solve(1, n);
    printf("%lld\n", res);
    return 0;
}
