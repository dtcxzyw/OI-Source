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
}
typedef long long Int64;
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
const int size = 50005;
struct Pos {
    int x, y, h;
} P[size];
bool cmpX(const Pos& a, const Pos& b) {
    return a.x < b.x;
}
bool cmpY(const Pos& a, const Pos& b) {
    return a.y < b.y;
}
Int64 A, B;
Int64 eval(const Pos& a) {
    return a.x * A + a.y * B;
}
struct Node {
    int l, r, minx, maxx, miny, maxy;
    Int64 sh;
    void update(const Node& rhs) {
        minx = std::min(minx, rhs.minx);
        maxx = std::max(maxx, rhs.maxx);
        miny = std::min(miny, rhs.miny);
        maxy = std::max(maxy, rhs.maxy);
        sh += rhs.sh;
    }
    Int64 evalMin() {
        return std::min(A * minx, A * maxx) +
            std::min(B * miny, B * maxy);
    }
    Int64 evalMax() {
        return std::max(A * minx, A * maxx) +
            std::max(B * miny, B * maxy);
    }
} T[size];
#define ls T[u].l
#define rs T[u].r
int build(int l, int r, bool axis) {
    if(l > r)
        return 0;
    int m = (l + r) >> 1;
    std::nth_element(P + l, P + m, P + r + 1,
                     axis ? cmpX : cmpY);
    T[m].minx = T[m].maxx = P[m].x;
    T[m].miny = T[m].maxy = P[m].y;
    T[m].sh = P[m].h;
    axis ^= 1;
    T[m].l = build(l, m - 1, axis);
    T[m].r = build(m + 1, r, axis);
    if(T[m].l)
        T[m].update(T[T[m].l]);
    if(T[m].r)
        T[m].update(T[T[m].r]);
    return m;
}
Int64 C, res;
void query(int u) {
    if(u == 0)
        return;
    if(T[u].evalMin() >= C)
        return;
    if(T[u].evalMax() < C) {
        res += T[u].sh;
        return;
    }
    if(eval(P[u]) < C)
        res += P[u].h;
    query(ls);
    query(rs);
}
int main() {
    IO::init();
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        P[i].x = read();
        P[i].y = read();
        P[i].h = read();
    }
    int rt = build(1, n, false);
    for(int i = 0; i < m; ++i) {
        A = read();
        B = read();
        C = read();
        res = 0;
        query(rt);
        printf("%lld\n", res);
    }
    return 0;
}
