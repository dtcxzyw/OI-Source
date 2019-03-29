#include <algorithm>
#include <cstdio>
const int N = 5000000, size = N + 5, mod = 1000000007;
typedef long long Int64;
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int p[size], S[size], pw[size];
bool flag[size];
void pre(int K) {
    S[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= N; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            pw[i] = powm(i, K);
            S[i] = sub(pw[i], 1);
        }
        for(int j = 1; j <= pcnt && i * p[j] <= N;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            Int64 si = S[i];
            if(i % p[j])
                S[val] = si * S[p[j]] % mod;
            else {
                S[val] = si * pw[p[j]] % mod;
                break;
            }
        }
    }
    for(int i = 1; i <= N; ++i)
        S[i] = add(S[i - 1], S[i]);
}
int main() {
    int T, K;
    scanf("%d%d", &T, &K);
    pre(K);
    for(int t = 0; t < T; ++t) {
        int n, m;
        scanf("%d%d", &n, &m);
        int end = std::min(n, m);
        Int64 res = 0;
        for(int i = 1; i <= end;) {
            int dn = n / i, dm = m / i,
                j = std::min(n / dn, m / dm);
            Int64 delta = S[j] - S[i - 1];
            res = (res + delta * dn % mod * dm) % mod;
            i = j + 1;
        }
        if(res < 0)
            res += mod;
        printf("%lld\n", res);
    }
    return 0;
}
