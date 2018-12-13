#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int mod = 1000000007;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
Int64 powm(Int64 x, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * x % mod;
        k >>= 1, x = x * x % mod;
    }
    return res;
}
Int64 inv(Int64 x) {
    return powm(x, mod - 2);
}
const int maxp = 15;
struct Poly {
    int k, fac[maxp];
    void construct(int* pv, int cv) {
        int base[maxp];
        for(int i = 1; i <= cv; ++i) {
            Int64 cur = 1;
            for(int j = 1; j <= cv; ++j) {
                if(j == i)
                    continue;
                cur = cur * (i - j) % mod;
            }
            base[i] = pv[i] * inv(cur) % mod;
        }
        k = cv;
        int L[maxp][maxp], R[maxp][maxp];
        L[0][0] = R[k + 1][0] = 1;
        for(int i = 1; i <= k; ++i) {
            L[i][0] = 0;
            for(int j = 1; j <= i; ++j)
                L[i][j] = L[i - 1][j - 1];
            for(int j = 0; j < i; ++j)
                L[i][j] = (L[i][j] -
                           asInt64(i) * L[i - 1][j]) %
                    mod;
        }
        for(int i = k; i >= 1; --i) {
            int c = k - i + 1;
            R[i][0] = 0;
            for(int j = 1; j <= c; ++j)
                R[i][j] = R[i + 1][j - 1];
            for(int j = 0; j < c; ++j)
                R[i][j] = (R[i][j] -
                           asInt64(i) * R[i + 1][j]) %
                    mod;
        }
        for(int i = 0; i < k; ++i)
            fac[i] = 0;
        for(int i = 1; i <= k; ++i) {
            int lc = i - 1, rc = k - i;
            Int64 bv = base[i];
            for(int j = 0; j <= lc; ++j)
                for(int k = 0; k <= rc; ++k) {
                    fac[j + k] =
                        (fac[j + k] +
                         bv * L[i - 1][j] % mod *
                             R[i + 1][k]) %
                        mod;
                }
        }
        for(int i = 0; i < k; ++i)
            if(fac[i] < 0)
                fac[i] += mod;
    }
    int operator()(int x) const {
        Int64 res = 0;
        for(int i = k - 1; i >= 0; --i)
            res = (res * x + fac[i]) % mod;
        return res;
    }
} p[maxp], d[maxp];
void prePoly(int k) {
    int end = k + 2;
    int pv[maxp][maxp], spv[maxp];
    for(int i = 1; i <= end; ++i) {
        pv[i][0] = 1;
        for(int j = 1; j <= k; ++j)
            pv[i][j] = asInt64(pv[i][j - 1]) * i % mod;
    }
    for(int i = 0; i <= k; ++i) {
        spv[0] = (i == 0);
        int end = i + 2;
        for(int j = 1; j <= end; ++j)
            spv[j] = add(spv[j - 1], pv[j][i]);
        p[i].construct(spv, end);
        for(int j = 1; j < end; ++j)
            spv[j] = sub(pv[j + 1][i], pv[j][i]);
        d[i].construct(spv, end - 1);
    }
}
struct PolyExpr {
    int a, b, c;
    PolyExpr(int a, int b, int c) : a(a), b(b), c(c) {}
    PolyExpr operator*(const PolyExpr& rhs) const {
        return PolyExpr(a + rhs.a, b + rhs.b,
                        asInt64(c) * rhs.c % mod);
    }
    bool operator<(const PolyExpr& rhs) const {
        return a != rhs.a ? a < rhs.a : b < rhs.b;
    }
    bool merge(const PolyExpr& rhs) {
        if(a == rhs.a && b == rhs.b) {
            c = add(c, rhs.c);
            return true;
        }
        return false;
    }
};
typedef std::vector<PolyExpr> SPE;
void prePolyExpr(std::vector<SPE>& expr, int k, int a,
                 int b) {
    SPE base;
    base.push_back(PolyExpr(1, 0, a));
    base.push_back(PolyExpr(0, 1, 1));
    base.push_back(PolyExpr(0, 0, b));
    expr.resize(k + 1);
    expr[0].push_back(PolyExpr(0, 0, 1));
    for(int i = 1; i <= k; ++i) {
        SPE cur, &last = expr[i - 1];
        cur.reserve(base.size() * last.size());
        for(int j = 0; j < base.size(); ++j)
            for(int k = 0; k < last.size(); ++k)
                cur.push_back(base[j] * last[k]);
        std::sort(cur.begin(), cur.end());
        PolyExpr cexp(0, 0, 0);
        SPE& post = expr[i];
        for(int j = 0; j < cur.size(); ++j) {
            if(!cexp.merge(cur[j])) {
                if(cexp.c)
                    post.push_back(cexp);
                cexp = cur[j];
            }
        }
        if(cexp.c)
            post.push_back(cexp);
    }
}
struct Mat {
    int A[15][15];
    int* operator[](int x) {
        return A[x];
    }
};
int mp;
Mat f(int n, int a, int b, int c) {
    Mat res;
    Int64 end = asInt64(a) * n + b;
    for(int i = 0; i <= mp; ++i)
        res[i][0] = p[i](n);
    if(end < c) {
        for(int i = 0; i <= mp; ++i) {
            for(int j = 1; i + j <= mp; ++j)
                res[i][j] = 0;
        }
    } else if(a == 0) {
        Int64 div = b / c;
        for(int i = 0; i <= mp; ++i) {
            Int64 k = res[i][0];
            for(int j = 1; i + j <= mp; ++j) {
                k = k * div % mod;
                res[i][j] = k;
            }
        }
    } else if(a >= c || b >= c) {
        int adc = a / c, amc = a % c, bdc = b / c,
            bmc = b % c;
        std::vector<SPE> expr;
        prePolyExpr(expr, mp, adc, bdc);
        Mat info = f(n, amc, bmc, c);
        for(int i = 0; i <= mp; ++i) {
            for(int j = 1; i + j <= mp; ++j) {
                int sum = 0;
                for(int k = 0; k < expr[j].size();
                    ++k) {
                    PolyExpr cexp = expr[j][k];
                    sum = (sum +
                           asInt64(cexp.c) *
                               info[i + cexp.a]
                                   [cexp.b]) %
                        mod;
                }
                res[i][j] = sum;
            }
        }
    } else {
        int m = end / c, nb = sub(sub(c, b), 1);
        Mat info = f(m - 1, c, nb, a);
        for(int i = 0; i <= mp; ++i) {
            Int64 l = res[i][0];
            for(int j = 1; i + j <= mp; ++j) {
                l = l * m % mod;
                int r = 0;
                Poly &p1 = p[i], &p2 = d[j];
                for(int x = 0; x < p1.k; ++x)
                    for(int y = 0; y < p2.k; ++y) {
                        r = (r +
                             asInt64(p1.fac[x]) *
                                 p2.fac[y] % mod *
                                 info[y][x]) %
                            mod;
                    }
                res[i][j] = sub(l, r);
            }
        }
    }
    return res;
}
int main() {
    prePoly(10);
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, a, b, c, k1, k2;
        scanf("%d%d%d%d%d%d", &n, &a, &b, &c, &k1,
              &k2);
        mp = k1 + k2;
        Mat res = f(n, a, b, c);
        printf("%d\n", res[k1][k2]);
    }
    return 0;
}
