#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 50005;
#define inf "2147483647"
struct Node {
    int ls, rs, siz;
} T[size * 256];
int icnt = 0, root[size] = {};
int queryImpl(int l, int r, int rt, int nl, int nr) {
    if (rt) {
        if (nl <= l && r <= nr)
            return T[rt].siz;
        else {
            int m = (l + r) >> 1, res = 0;
            if (nl <= m) res += queryImpl(l, m, T[rt].ls, nl, nr);
            if (m < nr) res += queryImpl(m + 1, r, T[rt].rs, nl, nr);
            return res;
        }
    }
    return 0;
}
int vsiz;
int query(int x, int kl, int kr) {
    int res = 0;
    while (x) {
        res += queryImpl(1, vsiz, root[x], kl, kr);
        x -= x & -x;
    }
    return res;
}
int query(int l, int r, int kl, int kr) {
    return query(r, kl, kr) - query(l - 1, kl, kr);
}
int queryKth(int l, int r, int k, int bl, int br) {
    if (bl == br)
        return bl;
    else {
        int m = (bl + br) >> 1;
        int lsiz = query(l, r, bl, m);
        if (k <= lsiz) return queryKth(l, r, k, bl, m);
        return queryKth(l, r, k - lsiz, m + 1, br);
    }
}
void modifyImpl(int l, int r, int &rt, int val, int op) {
    if (!rt) rt = ++icnt;
    T[rt].siz += op;
    if (l != r) {
        int m = (l + r) >> 1;
        if (val <= m)
            modifyImpl(l, m, T[rt].ls, val, op);
        else
            modifyImpl(m + 1, r, T[rt].rs, val, op);
    }
}
void modify(int x, int siz, int val, int op) {
    while (x <= siz) {
        modifyImpl(1, vsiz, root[x], val, op);
        x += x & -x;
    }
}
struct Op {
    int t, l, r, k;
} op[size];
int A[size], B[size * 2];
int find(int val) {
    return std::lower_bound(B + 1, B + vsiz + 1, val) - B;
}
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i) A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    int cnt = n;
    for (int i = 0; i < m; ++i) {
        op[i].t = read();
        op[i].l = read();
        op[i].r = read();
        if (op[i].t == 3)
            B[++cnt] = op[i].r;
        else
            op[i].k = read();
    }
    std::sort(B + 1, B + cnt + 1);
    vsiz = std::unique(B + 1, B + cnt + 1) - (B + 1);
    for (int i = 1; i <= n; ++i) {
        A[i] = find(A[i]);
        modify(i, n, A[i], 1);
    }
    for (int i = 0; i < m; ++i) {
        switch (op[i].t) {
            case 1: {
                int val = find(op[i].k);
                if (val == 1)
                    puts("1");
                else
                    printf("%d\n", query(op[i].l, op[i].r, 1, val - 1) + 1);
                break;
            }
            case 2: {
                printf("%d\n", B[queryKth(op[i].l, op[i].r, op[i].k, 1, vsiz)]);
                break;
            }
            case 3: {
                int x = op[i].l;
                modify(x, n, A[x], -1);
                A[x] = find(op[i].r);
                modify(x, n, A[x], 1);
                break;
            }
            case 4: {
                int val = find(op[i].k), num;
                if (val > 1 && (num = query(op[i].l, op[i].r, 1, val - 1)))
                    printf("%d\n", B[queryKth(op[i].l, op[i].r, num, 1, vsiz)]);
                else
                    puts("-" inf);
                break;
            }
            case 5: {
                int val = std::upper_bound(B + 1, B + vsiz + 1, op[i].k) - B, num;
                int base = op[i].r - op[i].l + 2;
                if (val <= vsiz && (num = query(op[i].l, op[i].r, val, vsiz)))
                    printf("%d\n", B[queryKth(op[i].l, op[i].r, base - num, 1, vsiz)]);
                else
                    puts(inf);
                break;
            }
        }
    }
    return 0;
}
