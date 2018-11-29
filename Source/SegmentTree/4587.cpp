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
struct Node {
    int sum, l, r;
} T[size * 20];
int icnt = 0, root[size], p, val;
int insert(int l, int r, int src) {
    int id = ++icnt;
    T[id] = T[src];
    T[id].sum += val;
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            T[id].l = insert(l, m, T[id].l);
        else
            T[id].r = insert(m + 1, r, T[id].r);
    }
    return id;
}
int nr, res;
void query(int l, int r, int a, int b) {
    if(r <= nr || T[a].sum == T[b].sum)
        res += T[a].sum - T[b].sum;
    else {
        int m = (l + r) >> 1;
        query(l, m, T[a].l, T[b].l);
        if(m < nr)
            query(m + 1, r, T[a].r, T[b].r);
    }
}
int A[size], B[size];
int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    int siz = std::unique(B + 1, B + n + 1) - (B + 1);
    for(int i = 1; i <= n; ++i) {
        val = A[i];
        p = std::lower_bound(B + 1, B + siz + 1, val) -
            B;
        root[i] = insert(1, siz, root[i - 1]);
    }
    int m = read();
    while(m--) {
        int l = read();
        int r = read();
        int x = 0;
        while(true) {
            res = 0,
            nr = std::upper_bound(B + 1, B + siz + 1,
                                  x + 1) -
                B - 1;
            if(nr)
                query(1, siz, root[r], root[l - 1]);
            if(res > x)
                x = res;
            else
                break;
        }
        printf("%d\n", x + 1);
    }
    return 0;
}
