#include <bitset>
#include <cstdio>
#include <cstring>
typedef long long Int64;
const int size = 2005, sizA = 105;
Int64 S[size];
std::bitset<sizA> F[sizA];
Int64 solveA(int n, int p, int A, int B) {
    Int64 res = 0;
    for(int i = p; i >= 0; --i) {
        Int64 st = res + (1LL << i) - 1;
        memset(F, 0, sizeof(F));
        F[0][0] = true;
        for(int j = 1; j <= n; ++j)
            for(int k = 0; k < j; ++k)
                if(((S[j] - S[k]) | st) == st)
                    F[j] |= F[k] << 1;
        bool flag = true;
        for(int k = A; k <= B; ++k)
            if(F[n][k]) {
                flag = false;
                break;
            }
        if(flag)
            res = st + 1;
    }
    return res;
}
int G[size];
Int64 solveB(int n, int p, int B) {
    Int64 res = 0;
    for(int i = p; i >= 0; --i) {
        Int64 st = res + (1LL << i) - 1;
        memset(G, 0x3f, sizeof(G));
        G[0] = 0;
        for(int j = 1; j <= n; ++j)
            for(int k = 0; k < j; ++k)
                if(((S[j] - S[k]) | st) == st)
                    G[j] = std::min(G[j], G[k] + 1);
        if(G[n] > B)
            res = st + 1;
    }
    return res;
}
int main() {
    int n, A, B;
    scanf("%d%d%d", &n, &A, &B);
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        S[i] = S[i - 1] + x;
    }
    int p = 0;
    while((1LL << p) < S[n])
        ++p;
    printf("%lld\n", A > 1 ? solveA(n, p, A, B) :
                             solveB(n, p, B));
    return 0;
}
