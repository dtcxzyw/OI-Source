#include <algorithm>
#include <cmath>
#include <cstdio>
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
const int size = 40005, modA = 39989,
          modB = 1000000009;
typedef double FT;
#define asFT static_cast<FT>
const FT inf = 1e20, eps = 1e-8;
int sign(FT x) {
    return (x > eps) - (x < -eps);
}
struct Line {
    FT k, b;
    int id;
    FT operator()(FT x) const {
        return k * x + b;
    }
} L[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void color(int l, int r, int id, const Line& B) {
    Line& A = L[id];
    if(A.id == 0) {
        A = B;
        return;
    }
    FT la = A(l), ra = A(r), lb = B(l), rb = B(r);
    int cl = sign(la - lb), cr = sign(ra - rb),
        sc = cl + cr;
    if(sc >= 1 || (cl == 0 && cr == 0 && A.id < B.id))
        return;
    if(sc <= -1 ||
       (cl == 0 && cr == 0 && A.id > B.id)) {
        A = B;
        return;
    }
    FT pos = (A.b - B.b) / (B.k - A.k);
    int m = (l + r) >> 1;
    if(pos <= m)
        color(ls, la > lb ? A : B);
    else
        color(rs, ra > rb ? A : B);
    if(pos <= m ? rb > ra : lb > la)
        A = B;
}
void modify(int l, int r, int id, int nl, int nr,
            const Line& line) {
    if(nl <= l && r <= nr)
        color(l, r, id, line);
    else {
        int m = (l + r) >> 1;
        if(nl <= m)
            modify(ls, nl, nr, line);
        if(m < nr)
            modify(rs, nl, nr, line);
    }
}
struct Pair {
    FT val;
    int id;
    Pair(FT val, int id) : val(val), id(id) {}
    bool operator<(const Pair& rhs) const {
        return sign(val - rhs.val) ? val < rhs.val :
                                     id > rhs.id;
    }
};
Pair query(int l, int r, int id, int p) {
    Pair res(L[id](p), L[id].id);
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            res = std::max(res, query(ls, p));
        else
            res = std::max(res, query(rs, p));
    }
    return res;
}
int main() {
    int n = read();
    int lastAns = 0, cnt = 0;
    for(int i = 1; i <= n; ++i) {
        if(read()) {
            int x1 = (read() + lastAns - 1) % modA + 1;
            int y1 = (read() + lastAns - 1) % modB + 1;
            int x2 = (read() + lastAns - 1) % modA + 1;
            int y2 = (read() + lastAns - 1) % modB + 1;
            Line line;
            if(x1 == x2) {
                line.k = 0.0;
                line.b = std::max(y1, y2);
            } else {
                line.k = asFT(y1 - y2) / asFT(x1 - x2);
                line.b = y1 - line.k * x1;
            }
            line.id = ++cnt;
            if(x1 > x2)
                std::swap(x1, x2);
            modify(1, modA, 1, x1, x2, line);
        } else {
            int x0 = (read() + lastAns - 1) % modA + 1;
            printf("%d\n",
                   lastAns = query(1, modA, 1, x0).id);
        }
    }
    return 0;
}
