#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
namespace IO {
    const int size = 1 << 23;
    char buf[size];
    char getc() {
        static char *S = 0, *T = 0;
        if(S == T)
            S = buf,
            T = S + fread(buf, 1, size, stdin);
        return S == T ? EOF : *S++;
    }
}
int read() {
    int res = 0, c;
    do
        c = IO::getc();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = IO::getc();
    }
    return res;
}
const int size = 500005;
int maxv[size * 8], off;
void update(int id) {
    int mv = std::max(maxv[id], maxv[id ^ 1]);
    maxv[id >> 1] += mv;
    maxv[id] -= mv, maxv[id ^ 1] -= mv;
}
void modify(int s, int t, int op) {
    for(s += off - 1, t += off + 1; s ^ t ^ 1;
        s >>= 1, t >>= 1) {
        if(~s & 1)
            maxv[s ^ 1] += op;
        if(t & 1)
            maxv[t ^ 1] += op;
        update(s);
        update(t);
    }
    while(s > 1) {
        update(s);
        s >>= 1;
    }
}
const int inf = 1 << 30;
struct Range {
    int l, r, len;
    bool operator<(const Range& rhs) const {
        return len < rhs.len;
    }
} R[size];
int P[size * 2], siz;
int find(int x) {
    return std::lower_bound(P + 1, P + siz + 1, x) - P;
}
int main() {
    int n = read();
    int m = read();
    siz = 0;
    for(int i = 1; i <= n; ++i) {
        R[i].l = read();
        R[i].r = read();
        R[i].len = R[i].r - R[i].l;
        P[++siz] = R[i].l;
        P[++siz] = R[i].r;
    }
    std::sort(P + 1, P + siz + 1);
    siz = std::unique(P + 1, P + siz + 1) - (P + 1);
    for(int i = 1; i <= n; ++i)
        R[i].l = find(R[i].l), R[i].r = find(R[i].r);
    std::sort(R + 1, R + n + 1);
    off = 1;
    while(off < (siz + 2))
        off <<= 1;
    int res = inf;
    for(int l = 1, r = 0; l <= n; ++l) {
        while(r < n && maxv[1] < m) {
            ++r;
            modify(R[r].l, R[r].r, 1);
        }
        if(maxv[1] >= m) {
            res = std::min(R[r].len - R[l].len, res);
            modify(R[l].l, R[l].r, -1);
        } else
            break;
    }
    if(res == inf)
        puts("-1");
    else
        printf("%d\n", res);
    return 0;
}
