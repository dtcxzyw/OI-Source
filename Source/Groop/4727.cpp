#include <algorithm>
#include <cstdio>
const int mod = 997, phi = mod - 1, size = 65;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int inv[mod], p2[mod], L[size], c[size], ccnt = 0,
                                         ans = 0;
void DFS(int n, int maxl, int a, int b) {
    if(n) {
        for(int i = 1; i <= maxl; ++i) {
            int nb = (b + (i >> 1)) % phi;
            for(int j = 1; j <= ccnt; ++j)
                nb = (nb + gcd(L[j], i)) % phi;
            L[++ccnt] = i, ++c[i];
            int na = a * c[i] * i % mod;
            DFS(n - i, std::min(n - i, i), na, nb);
            --ccnt, --c[i];
        }
    } else
        ans = (ans + inv[a] * p2[b]) % mod;
}
int main() {
    inv[1] = 1;
    for(int i = 2; i < mod; ++i)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    p2[0] = 1;
    for(int i = 1; i < phi; ++i)
        p2[i] = (p2[i - 1] << 1) % mod;
    int n;
    scanf("%d", &n);
    DFS(n, n, 1, 0);
    printf("%d\n", ans);
    return 0;
}
