#include <algorithm>
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
const int N = 50000, size = N + 5;
int p[size], mu[size];
bool flag[size];
void pre() {
    mu[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= N; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= N;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                mu[val] = -mu[i];
            else
                break;
        }
    }
    for(int i = 1; i <= N; ++i)
        mu[i] += mu[i - 1];
}
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 S[size];
int main() {
    pre();
    for(int i = 1; i <= N; ++i) {
        for(int j = i; j <= N; j += i)
            ++S[j];
    }
    for(int i = 1; i <= N; ++i)
        S[i] += S[i - 1];
    int t = read();
    for(int x = 0; x < t; ++x) {
        int n = read();
        int m = read();
        int end = std::min(n, m);
        Int64 res = 0;
        for(int i = 1; i <= end;) {
            int dn = n / i, dm = m / i,
                j = std::min(n / dn, m / dm);
            res += asInt64(mu[j] - mu[i - 1]) * S[dn] *
                S[dm];
            i = j + 1;
        }
        printf("%lld\n", res);
    }
    return 0;
}
