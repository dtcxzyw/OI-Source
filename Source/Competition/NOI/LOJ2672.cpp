// FIXME
#include <cstdio>
#include <vector>
namespace IO {
    char in[1 << 24];
    void init() {
        fread(in, 1, sizeof(in), stdin);
    }
    char getc() {
        static char* S = in;
        return *S++;
    }
}
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = IO::getc();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return flag ? -res : res;
}
const int size = 500005;
struct Node {
    int l, r, gcdv;
} T[size * 40];
int tcnt = 0;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
void modify1D(int l, int r, int id, int p, int val) {
    if(l == r)
        T[id].gcdv += val;
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            modify1D(l, m, T[id].l, p, val);
        else
            modify1D(m + 1, r, T[id].r, p, val);
        T[id].gcdv =
            gcd(T[T[id].l].gcdv, T[T[id].r].gcdv);
    }
}
int query1D(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return T[id].gcdv;
    int m = (l + r) >> 1, gcdv = 0;
    if(nl <= m)
        gcdv = query1D(l, m, T[id].l, nl, nr);
    if(m < nr)
        gcdv = gcd(gcdv,
                   query1D(m + 1, r, T[id].r, nl, nr));
    return gcdv;
}
int rt[size << 2], M;
int query2D(int l, int r, int id, int lx, int rx,
            int ly, int ry) {
    if(lx <= l && r <= rx)
        return query1D(1, M, rt[id], ly, ry);
    int m = (l + r) >> 1, gcdv = 0;
    if(lx <= m)
        gcdv = query2D(l, m, id << 1, lx, rx, ly, ry);
    if(m < rx)
        gcdv = gcd(gcdv, query2D(m + 1, r, id << 1 | 1,
                                 lx, rx, ly, ry));
    return gcdv;
}
void update(int l, int r, int id, int rtA, int rtB,
            int p) {
    if(l == r)
        T[id].gcdv = gcd(T[rtA].gcdv, T[rtB].gcdv);
    else {
        int m = (l + r) >> 1;
        if(p <= m)
            update(l, m, T[id].l, T[rtA].l, T[rtB].l,
                   p);
        else
            update(m + 1, r, T[id].r, T[rtA].r,
                   T[rtB].r, p);
        T[id].gcdv =
            gcd(T[T[id].l].gcdv, T[T[id].r].gcdv);
    }
}
void modify2D(int l, int r, int id, int px, int py,
              int val) {
    if(l == r)
        modify1D(1, M, rt[id], py, val);
    else {
        int m = (l + r) >> 1;
        if(px <= m)
            modify2D(l, m, id << 1, px, py, val);
        else
            modify2D(m + 1, r, id << 1 | 1, px, py,
                     val);
        update(1, M, rt[id], rt[id << 1],
               rt[id << 1 | 1], py);
    }
}
std::vector<int> A[size];
int build1D(int l, int r, int p) {
    int id = ++tcnt;
    if(l == r)
        T[id].gcdv = A[p][l] - A[p][l - 1] -
            A[p - 1][l] + A[p - 1][l - 1];
    else {
        int m = (l + r) >> 1;
        T[id].l = build1D(l, m, p);
        T[id].r = build1D(m + 1, r, p);
        T[id].gcdv =
            gcd(T[T[id].l].gcdv, T[T[id].r].gcdv);
    }
    return id;
}
int merge2D(int l, int r, int rtA, int rtB) {
    int id = ++tcnt;
    T[id].gcdv = gcd(T[rtA].gcdv, T[rtB].gcdv);
    if(l != r) {
        int m = (l + r) >> 1;
        T[id].l = merge2D(l, m, T[rtA].l, T[rtB].l);
        T[id].r =
            merge2D(m + 1, r, T[rtA].r, T[rtB].r);
    }
    return id;
}
void build2D(int l, int r, int id) {
    if(l == r)
        rt[id] = build1D(1, M, l);
    else {
        int m = (l + r) >> 1;
        build2D(l, m, id << 1);
        build2D(m + 1, r, id << 1 | 1);
        rt[id] = merge2D(1, M, rt[id << 1],
                         rt[id << 1 | 1]);
    }
}
int main() {
    IO::init();
    int N = read();
    M = read();
    int x = read();
    int y = read();
    int t = read();
    A[0].resize(M + 1);
    for(int i = 1; i <= N; ++i) {
        A[i].resize(M + 1);
        for(int j = 1; j <= M; ++j)
            A[i][j] = read();
    }
    build2D(1, N, 1);
    for(int i = 1; i <= t; ++i) {
        int op = read();
        int x1 = read();
        int y1 = read();
        int x2 = read();
        int y2 = read();
        if(op) {
            int c = read();
            modify2D(1, N, 1, x1, y1, c);
            if(x2 < N)
                modify2D(1, N, 1, x2 + 1, y1, -c);
            if(y2 < M)
                modify2D(1, N, 1, x1, y2 + 1, -c);
            if(x2 < N && y2 < M)
                modify2D(1, N, 1, x2 + 1, y2 + 1, c);
        } else {
            x1 = x - x1, x2 = x + x2, y1 = y - y1,
            y2 = y + y2;
            printf("%d\n",
                   query2D(1, N, 1, x1, x2, y1, y2));
        }
    }
    return 0;
}
