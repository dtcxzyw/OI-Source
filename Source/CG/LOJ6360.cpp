#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
typedef double FT;
const int maxN = 20005, maxM = 5;
int m;
struct Vec {
    FT x[maxM];
    void clear() {
        memset(x, 0, sizeof(FT) * m);
    }
    FT operator[](int id) const {
        return x[id];
    }
    FT& operator[](int id) {
        return x[id];
    }
    Vec operator+(const Vec& rhs) const {
        Vec res;
        for(int i = 0; i < m; ++i)
            res[i] = x[i] + rhs[i];
        return res;
    }
    Vec operator-(const Vec& rhs) const {
        Vec res;
        for(int i = 0; i < m; ++i)
            res[i] = x[i] - rhs[i];
        return res;
    }
    Vec operator*(FT k) const {
        Vec res;
        for(int i = 0; i < m; ++i)
            res[i] = x[i] * k;
        return res;
    }
    FT length2() const {
        FT res = 0;
        for(int i = 0; i < m; ++i)
            res += x[i] * x[i];
        return res;
    }
} P[maxN], st[maxM + 5], D[5];
FT dot(const Vec& a, const Vec& b) {
    FT res = 0;
    for(int i = 0; i < m; ++i)
        res += a[i] * b[i];
    return res;
}
const FT eps = 1e-8;
struct Circle {
    Vec ori;
    FT r2;
    Circle(const Vec& ori, FT r2) : ori(ori), r2(r2) {}
    bool out(const Vec& p) const {
        return (p - ori).length2() > r2 + eps;
    }
};
FT A[5][6], X[5];
void gauss(int n) {
    for(int i = 0; i < n; ++i) {
        int x = i;
        for(int j = i + 1; j < n; ++j)
            if(fabs(A[x][i]) < fabs(A[j][i]))
                x = j;
        if(x != i) {
            for(int j = i; j <= n; ++j)
                std::swap(A[i][j], A[x][j]);
        }
        for(int j = i + 1; j < n; ++j) {
            FT fac = A[j][i] / A[i][i];
            for(int k = i; k <= n; ++k)
                A[j][k] -= fac * A[i][k];
        }
    }
    for(int i = n - 1; i >= 0; --i) {
        FT sum = A[i][n];
        for(int j = i + 1; j < n; ++j)
            sum -= X[j] * A[i][j];
        X[i] = sum / A[i][i];
    }
}
Circle makeCircle(int siz) {
    switch(siz) {
        case 1:
            return Circle(st[0], 0.0);
            break;
        case 2: {
            Vec mid = (st[0] + st[1]) * 0.5;
            return Circle(mid,
                          (st[0] - mid).length2());
        } break;
        default: {
            for(int i = 1; i < siz; ++i)
                D[i - 1] = st[i] - st[0];
            --siz;
            for(int i = 0; i < siz; ++i) {
                for(int j = 0; j < siz; ++j)
                    A[i][j] = dot(D[i], D[j]);
                A[i][siz] = D[i].length2() * 0.5;
            }
            gauss(siz);
            Vec ori;
            ori.clear();
            for(int i = 0; i < siz; ++i)
                ori = ori + D[i] * X[i];
            return Circle(ori + st[0], ori.length2());
        } break;
    }
}
Circle cur(Vec(), 0.0);
void DFS(int i, int top) {
    st[top - 1] = P[i];
    cur = makeCircle(top);
    if(top <= m)
        for(int j = 0; j < i; ++j)
            if(cur.out(P[j]))
                DFS(j, top + 1);
}
int main() {
    int n;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            scanf("%lf", &P[i][j]);
    std::random_shuffle(P, P + n);
    for(int i = 0; i < n; ++i)
        if(cur.out(P[i]))
            DFS(i, 1);
    for(int i = 0; i < m; ++i)
        printf("%lf ", cur.ori[i]);
    puts("");
    return 0;
}
