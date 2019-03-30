#include <algorithm>
#include <cstdio>
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
void print(int x) {
    if(x >= 10)
        print(x / 10);
    IO::putc('0' + x % 10);
}
const int size = 500005;
struct Vec {
    int x, y;
} P[size];
typedef long long Int64;
Int64 dis2(const Vec& a, const Vec& b) {
    Int64 dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
int n, A[size];
void solve(int l, int r, int b, int e) {
    if(l > r)
        return;
    int m = (l + r) >> 1, beg = std::max(b, m),
        end = std::min(e, m + n - 1), tp = 0, tid = 0;
    Int64 dpv = -1;
    for(int i = beg; i <= end; ++i) {
        int id = i > n ? i - n : i;
        Int64 cur = dis2(P[m], P[id]);
        if(cur > dpv || (cur == dpv && id < tid))
            tp = i, tid = id, dpv = cur;
    }
    A[m] = tid;
    solve(l, m - 1, b, tp);
    solve(m + 1, r, tp, e);
}
void foo() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    solve(1, n, 1, n * 2);
    for(int i = 1; i <= n; ++i) {
        print(A[i]);
        IO::putc('\n');
    }
}
int main() {
    IO::init();
    int t = read();
    for(int i = 0; i < t; ++i)
        foo();
    IO::uninit();
    return 0;
}
