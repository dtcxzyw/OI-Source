#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
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
    char out[1 << 21], *S = out;
    void putc(char c) {
        *S++ = c;
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
const int size = 1000005;
struct Pos {
    int x, y;
} P[size];
bool cmpX(const Pos& a, const Pos& b) {
    return a.x < b.x;
}
bool cmpY(const Pos& a, const Pos& b) {
    return a.y < b.y;
}
int iabs(int x) {
    return x >= 0 ? x : -x;
}
int dist(const Pos& a, const Pos& b) {
    return iabs(a.x - b.x) + iabs(a.y - b.y);
}
struct Node {
    int l, r, minx, maxx, miny, maxy;
    void update(const Node& rhs) {
        minx = std::min(minx, rhs.minx);
        maxx = std::max(maxx, rhs.maxx);
        miny = std::min(miny, rhs.miny);
        maxy = std::max(maxy, rhs.maxy);
    }
    int evalMin(const Pos& pos) {
        int dx = std::max(
            std::max(minx - pos.x, pos.x - maxx), 0);
        int dy = std::max(
            std::max(miny - pos.y, pos.y - maxy), 0);
        return dx + dy;
    }
} T[size];
#define ls T[u].l
#define rs T[u].r
int build(int l, int r) {
    if(l > r)
        return 0;
    int axis = rand() & 1, m = (l + r) >> 1;
    std::nth_element(P + l, P + m, P + r + 1,
                     axis ? cmpX : cmpY);
    T[m].minx = T[m].maxx = P[m].x;
    T[m].miny = T[m].maxy = P[m].y;
    T[m].l = build(l, m - 1);
    if(T[m].l)
        T[m].update(T[T[m].l]);
    T[m].r = build(m + 1, r);
    if(T[m].r)
        T[m].update(T[T[m].r]);
    return m;
}
int res;
void query(const Pos& p, int u) {
    if(u == 0)
        return;
    res = std::min(res, dist(p, P[u]));
    int le = T[ls].evalMin(p), re = T[rs].evalMin(p);
    if(le < re) {
        if(le < res)
            query(p, ls);
        if(re < res)
            query(p, rs);
    } else {
        if(re < res)
            query(p, rs);
        if(le < res)
            query(p, ls);
    }
}
std::vector<std::pair<int, int>> rts;
void insert(int u) {
    int cur = 1;
    while(rts.size() && rts.back().first == cur) {
        cur += rts.back().first;
        rts.pop_back();
    }
    rts.push_back(
        std::make_pair(cur, build(u - cur + 1, u)));
}
int main() {
    IO::init();
    srand(19260817);
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        P[i].x = read();
        P[i].y = read();
    }
    rts.push_back(std::make_pair(n, build(1, n)));
    int pcnt = n;
    for(int i = 1; i <= m; ++i) {
        int t = read();
        Pos p;
        p.x = read();
        p.y = read();
        if(t == 1) {
            P[++pcnt] = p;
            insert(pcnt);
        } else {
            res = INT_MAX;
            for(size_t j = 0; j < rts.size(); ++j)
                query(p, rts[j].second);
            write(res);
            IO::putc('\n');
        }
    }
    IO::uninit();
    return 0;
}
