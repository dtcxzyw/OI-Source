#include <cmath>
#include <cstdio>
typedef long long Int64;
int mod, map[13][13];
struct Poly {
    int A[12];
    Poly operator+(const Poly& rhs) const {
        Poly res;
        for(int i = 0; i < mod; ++i)
            res.A[i] = A[i] + rhs.A[i];
        return res;
    }
    Poly operator-(const Poly& rhs) const {
        Poly res;
        for(int i = 0; i < mod; ++i)
            res.A[i] = A[i] - rhs.A[i];
        return res;
    }
};
const int sqsiz = 200005;
int p[sqsiz], psiz = 0;
Poly sumf[sqsiz];
bool flag[sqsiz];
void pre(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++psiz] = i;
            sumf[psiz] = sumf[psiz - 1];
            ++sumf[psiz].A[i % mod];
        }
        for(int j = 1; j <= psiz && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
Poly G[2][sqsiz];
Int64 sqr, n;
Poly& getG(Int64 x) {
    if(x <= sqr)
        return G[0][x];
    return G[1][n / x];
}
Int64 q[sqsiz * 2];
int main() {
    scanf("%lld%d", &n, &mod);
    for(int i = 0; i < mod; ++i)
        for(int j = 0; j < mod; ++j)
            map[i][j] = i * j % mod;
    sqr = sqrt(n);
    pre(sqr);
    int m = 0;
    Int64 dv = 1;
    while(dv <= n) {
        Int64 val = n / dv;
        Poly& A = getG(val);
        Int64 div = val / mod, mv = val % mod;
        for(int i = 0; i < mod; ++i)
            A.A[i] = div + (mv >= i);
        --A.A[0], --A.A[1];
        q[++m] = val;
        dv = n / val + 1;
    }
    for(int i = 1; i <= psiz; ++i) {
        Int64 cp = p[i], cp2 = cp * cp,
              mask = cp % mod;
        for(int j = 1; j <= m && cp2 <= q[j]; ++j) {
            Int64 x = q[j];
            Poly& val = getG(x);
            Poly delta = getG(x / cp) - sumf[i - 1];
            for(int k = 0; k < mod; ++k)
                val.A[map[mask][k]] -= delta.A[k];
        }
    }
    Poly A = getG(n);
    for(int i = 0; i < mod; ++i)
        printf("%d\n", A.A[i]);
    return 0;
}
