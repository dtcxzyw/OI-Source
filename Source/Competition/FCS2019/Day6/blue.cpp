#include <algorithm>
#include <cstdio>
#include <cstring>
struct Map {
    int A[26];
    Map operator*(const Map& rhs) const {
        Map res;
        for(int i = 0; i < 26; ++i)
            res.A[i] = A[rhs.A[i]];
        return res;
    }
    int operator()(int ch) const {
        return A[ch];
    }
};
Map pow(Map a, int k) {
    Map res;
    for(int i = 0; i < 26; ++i)
        res.A[i] = i;
    while(k) {
        if(k & 1)
            res = res * a;
        k >>= 1, a = a * a;
    }
    return res;
}
const int size = 200005;
char buf[30], S[2][size], T[size];
bool perform(const char* F, char* G, int n, int a,
             const Map& trans) {
    bool res = true;
    for(int i = 1, j = a + 1; i <= n; ++i) {
        G[i] = trans(F[j]);
        res &= G[i] == T[i];
        if(++j > n)
            j = 1;
    }
    return res;
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int calcCycle(const Map& trans) {
    bool flag[26] = {};
    int res = 1;
    for(int i = 0; i < 26; ++i)
        if(!flag[i]) {
            int csiz = 0, x = i;
            do {
                ++csiz;
                flag[x] = true;
                x = trans(x);
            } while(!flag[x]);
            res = res / gcd(res, csiz) * csiz;
        }
    return res;
}
int CS[26], CT[26];
int main() {
    int n, a, b;
    scanf("%d%d%d%s%s%s", &n, &a, &b, buf, S[0] + 1,
          T + 1);
    for(int i = 1; i <= n; ++i) {
        S[0][i] -= 'a', T[i] -= 'a';
        ++CS[S[0][i]];
        ++CT[T[i]];
    }
    std::sort(CS, CS + 26);
    std::sort(CT, CT + 26);
    if(memcmp(CS, CT, sizeof(int) * 26) != 0) {
        puts("-1");
        return 0;
    }
    Map base;
    for(int i = 0; i < 26; ++i)
        base.A[i] = buf[i] - 'a';
    Map trans = pow(base, b);
    char *F = S[0], *G = S[1];
    a %= n;
    long long end = n / gcd(a, n);
    int c = calcCycle(trans);
    end = std::max(end / gcd(end, c) * c, 1LL);
    fprintf(stderr, "%lld\n", end);
    for(int i = 1; i <= end; ++i) {
        if(perform(F, G, n, a, trans)) {
            printf("%d\n", i);
            return 0;
        }
        std::swap(F, G);
    }
    puts("-1");
    return 0;
}
