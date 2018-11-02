// TODO
#include <cctype>
#include <cstdio>
#include <cstdlib>
typedef double FT;
const FT eps = 1e-10, inf = 1e20;
FT read() {
    char str[30];
    int p = 0, c;
    do
        c = getchar();
    while(!isgraph(c));
    while(isgraph(c)) {
        str[p++] = c;
        c = getchar();
    }
    str[p] = '\0';
    return strtod(str, 0);
}
const int size = 1 << 20;
FT P[size], SP[size], E[size];
int main() {
    int n;
    scanf("%d", &n);
    int end = 1 << n;
    for(int i = 0; i < end; ++i)
        P[i] = read();
    for(int i = 1; i < end; ++i) {
        for(int j = i; j; j = (j - 1) & i)
            SP[i] += P[i ^ j];
    }
    E[0] = 0.0;
    for(int i = 1; i < end; ++i) {
        FT csp = 0.0, fsp = SP[i] + P[i], se = 0.0;
        for(int s = i; s; s = (s - 1) & i) {
            int t = i ^ s;
            FT p = fsp - SP[s];
            if(E[t] != inf && p > eps) {
                se += p * E[t];
            }
        }
        if(sp > eps) {
            if(P[0] > eps) {

            } else
                E[i] = se / sp + 1.0;
        } else
            E[i] = inf;
    }
    FT ans = E[end - 1];
    if(ans == inf)
        puts("INF");
    else
        printf("%.10lf\n", ans);
    return 0;
}
