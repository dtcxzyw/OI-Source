#include <cmath>
#include <cstdio>
const int size = 50000;
typedef double FT;
struct Line {
    FT k, b;
    FT operator()(FT x) const {
        return fma(k, x, b);
    }
} L[(size + 5) << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void insert(int l, int r, int id, const Line& B) {
    Line& A = L[id];
    FT la = A(l), ra = A(r), lb = B(l), rb = B(r);
    if(la > lb && ra > rb)
        return;
    if(lb > la && rb > ra) {
        A = B;
        return;
    }
    FT pos = (A.b - B.b) / (B.k - A.k);
    int m = (l + r) >> 1;
    if(l != r) {
        if(pos <= m)
            insert(ls, la > lb ? A : B);
        else
            insert(rs, ra > rb ? A : B);
    }
    if(pos <= m ? rb > ra : lb > la)
        A = B;
}
FT query(int l, int r, int id, int p) {
    FT res = L[id](p);
    if(l != r) {
        int m = (l + r) >> 1;
        if(p <= m)
            res = fmax(res, query(ls, p));
        else
            res = fmax(res, query(rs, p));
    }
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    char op[15];
    for(int i = 1; i <= n; ++i) {
        scanf("%s", op);
        if(op[0] == 'P') {
            Line line;
            scanf("%lf%lf", &line.b, &line.k);
            line.b -= line.k;
            insert(1, size, 1, line);
        } else {
            int p;
            scanf("%d", &p);
            int res = query(1, size, 1, p);
            printf("%d\n", res / 100);
        }
    }
    return 0;
}
