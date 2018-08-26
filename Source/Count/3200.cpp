#include <cstdio>
typedef long long Int64;
Int64 powm(Int64 a, int k, int p) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % p;
        k >>= 1, a = a * a % p;
    }
    return res;
}
const int size = 2000005, psiz = 150005;
int pcnt = 0, prime[psiz], fac[size];
bool flag[size];
void init(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            prime[++pcnt] = i;
            fac[i] = pcnt;
        }
        for(int j = 1; j <= pcnt; ++j) {
            int val = i * prime[j];
            if(val > n)
                break;
            flag[val] = true;
            fac[val] = j;
            if(i % prime[j] == 0)
                break;
        }
    }
}
int cnt[psiz];
void count(int n, int op) {
    while(n != 1) {
        cnt[fac[n]] += op;
        n /= prime[fac[n]];
    }
}
int main() {
    int n, p;
    scanf("%d%d", &n, &p);
    int end = 2 * n;
    init(end);
    for(int i = n + 2; i <= end; ++i)
        count(i, 1);
    for(int i = 1; i <= n; ++i)
        count(i, -1);
    Int64 res = 1;
    for(int i = 1; i <= pcnt; ++i)
        res = res * powm(prime[i], cnt[i], p) % p;
    printf("%lld\n", res);
    return 0;
}
