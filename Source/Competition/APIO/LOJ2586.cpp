#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <random>
namespace IO {
    char in[1 << 24];
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
void write(int x) {
    if(x >= 10)
        write(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 300005;
typedef long long Int64;
struct Circle {
    int x, y, r, id;
    bool intersect(const Circle& rhs) const {
        Int64 dx = x - rhs.x, dy = y - rhs.y,
              sr = r + rhs.r;
        return dx * dx + dy * dy <= sr * sr;
    }
} C[size];
struct Node {
    int x[2], y[2], id, l, r, siz;
    void update(const Node& c) {
        x[0] = std::min(x[0], c.x[0]);
        x[1] = std::max(x[1], c.x[1]);
        y[0] = std::min(y[0], c.y[0]);
        y[1] = std::max(y[1], c.y[1]);
    }
    bool intersect(const Circle& C) const {
        Int64 cx = C.x, cy = C.y, cr = C.r;
        Int64 dx = std::max(
            std::max(x[0] - cx, cx - x[1]), 0LL);
        Int64 dy = std::max(
            std::max(y[0] - cy, cy - y[1]), 0LL);
        return dx * dx + dy * dy <= cr * cr;
    }
} T[size];
std::mt19937_64
    eng(std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count());
std::uniform_real_distribution<double> urd(0.0,
                                           acos(-1.0));
int build(int l, int r) {
    int m = (l + r) >> 1;
    double angle = urd(eng), bx = cos(angle),
           by = sin(angle);
    std::nth_element(
        C + l, C + m, C + r + 1,
        [=](const Circle& a, const Circle& b) {
            return bx * a.x + by * a.y <
                bx * b.x + by * b.y;
        });
    T[m].x[0] = C[m].x - C[m].r;
    T[m].x[1] = C[m].x + C[m].r;
    T[m].y[0] = C[m].y - C[m].r;
    T[m].y[1] = C[m].y + C[m].r;
    T[m].id = C[m].id;
    T[m].siz = r - l + 1;
    if(l < m) {
        T[m].l = build(l, m - 1);
        T[m].update(T[T[m].l]);
    }
    if(m < r) {
        T[m].r = build(m + 1, r);
        T[m].update(T[T[m].r]);
    }
    return m;
}
int did[size];
#define ls T[u].l
#define rs T[u].r
void modify(int u, const Circle& X) {
    if(u == 0 || T[u].x[0] > T[u].x[1] ||
       !T[u].intersect(X))
        return;
    int cid = T[u].id;
    if(!did[cid] && C[u].intersect(X))
        did[cid] = X.id;
    modify(ls, X);
    modify(rs, X);
    T[u].x[0] = std::min(T[ls].x[0], T[rs].x[0]);
    T[u].x[1] = std::max(T[ls].x[1], T[rs].x[1]);
    T[u].y[0] = std::min(T[ls].y[0], T[rs].y[0]);
    T[u].y[1] = std::max(T[ls].y[1], T[rs].y[1]);
    if(!did[cid]) {
        T[u].x[0] =
            std::min(T[u].x[0], C[u].x - C[u].r);
        T[u].x[1] =
            std::max(T[u].x[1], C[u].x + C[u].r);
        T[u].y[0] =
            std::min(T[u].y[0], C[u].y - C[u].r);
        T[u].y[1] =
            std::max(T[u].y[1], C[u].y + C[u].r);
    }
}
int rk[size];
bool cmpR(int a, int b) {
    return C[a].r == C[b].r ? C[a].id < C[b].id :
                              C[a].r > C[b].r;
}
const int inf = 1 << 30;
int main() {
    T[0].x[0] = T[0].y[0] = inf;
    T[0].x[1] = T[0].y[1] = -inf;
    IO::init();
    int n = read();
    for(int i = 1; i <= n; ++i) {
        C[i].id = i;
        C[i].x = read();
        C[i].y = read();
        C[i].r = read();
    }
    int rt = build(1, n);
    for(int i = 1; i <= n; ++i)
        rk[i] = i;
    std::sort(rk + 1, rk + n + 1, cmpR);
    for(int i = 1; i <= n; ++i) {
        int u = rk[i];
        if(!did[C[u].id])
            modify(rt, C[u]);
    }
    for(int i = 1; i <= n; ++i) {
        write(did[i]);
        IO::putc(' ');
    }
    IO::uninit();
    return 0;
}
