#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100000;
typedef double FT;
const FT inf = 1e20;
#define asFT static_cast<FT>
struct Line {
    FT k, b;
    FT operator()(FT x) const {
        return k * x + b;
    }
} L[(size + 5) << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void build(int l, int r, int id) {
    L[id].b = -inf;
    if(l != r) {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
    }
}
void color(int l, int r, int id, const Line& B) {
    Line& A = L[id];
    FT la = A(l), ra = A(r), lb = B(l), rb = B(r);
    if(la >= lb && ra >= rb)
        return;
    if(la <= lb && ra <= rb) {
        A = B;
        return;
    }
    int m = (l + r) >> 1;
    FT pos = (A.b - B.b) / (B.k - A.k);
    if(pos <= m)
        color(ls, la > lb ? A : B);
    else
        color(rs, ra > rb ? A : B);
    if(pos <= m ? rb > ra : lb > la)
        A = B;
}
void insert(int l, int r, int id, int nl, int nr,
            const Line& line) {
    if(nl <= l && r <= nr)
        color(l, r, id, line);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            insert(ls, nl, nr, line);
        if(m < nr)
            insert(rs, nl, nr, line);
    }
}
FT query(int l, int r, int id, int p) {
    FT res = L[id](p);
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            res = std::max(res, query(ls, p));
        else
            res = std::max(res, query(rs, p));
    }
    return res;
}
void addSeg() {
    int x1 = read();
    int y1 = read();
    int x2 = read();
    int y2 = read();
    if(std::max(x1, x2) < 1 || std::min(x1, x2) > size)
        return;
    Line line;
    if(x1 == x2) {
        line.k = 0.0;
        line.b = std::max(y1, y2);
    } else {
        line.k = (y1 - y2) / asFT(x1 - x2);
        line.b = y1 - line.k * x1;
    }
    if(x1 > x2)
        std::swap(x1, x2);
    insert(1, size, 1, x1, x2, line);
}
int main() {
    int n = read();
    int m = read();
    build(1, size, 1);
    for(int i = 1; i <= n; ++i)
        addSeg();
    for(int i = 1; i <= m; ++i) {
        if(read()) {
            int x0 = read();
            FT res = query(1, size, 1, x0);
            if(res < -1e19)
                puts("0");
            else
                printf("%.3lf\n", res);
        } else
            addSeg();
    }
    return 0;
}
