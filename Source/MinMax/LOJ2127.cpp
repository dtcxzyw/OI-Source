#include <cctype>
#include <cstdio>
#include <cstdlib>
typedef double FT;
const FT eps = 1.0 - 1e-8;
FT readFT() {
    int c;
    do
        c = getchar();
    while(!isgraph(c));
    char str[32];
    int pos = 0;
    while(isgraph(c)) {
        str[pos++] = c;
        c = getchar();
    }
    str[pos] = '\0';
    return strtod(str, 0);
}
const int size = 1 << 20;
FT P[size];
int bc[size];
int main() {
    int n;
    scanf("%d", &n);
    int end = 1 << n;
    for(int i = 0; i < end; ++i)
        P[i] = readFT();
    for(int i = 1; i < end; i <<= 1)
        for(int j = 0; j < end; ++j)
            if(j & i)
                P[j] += P[j ^ i];
    int mask = end - 1;
    FT ans = 0.0;
    for(int i = 1; i < end; ++i) {
        bc[i] = bc[i >> 1] + (i & 1);
        FT p = P[mask ^ i];
        if(p >= eps) {
            puts("INF");
            return 0;
        }
        FT w = 1.0 / (1.0 - p);
        if(bc[i] & 1)
            ans += w;
        else
            ans -= w;
    }
    printf("%.10lf\n", ans);
    return 0;
}
