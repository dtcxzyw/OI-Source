// P3175
#include <cctype>
#include <cstdio>
#include <cstdlib>
typedef double FT;
const FT eps = 1.0 - 1e-8;
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
FT P[size], A[size];
int main() {
    int n;
    scanf("%d", &n);
    int end = 1 << n;
    for(int i = 0; i < end; ++i)
        P[i] = read();
    A[0] = (n & 1 ? -1.0 : 1.0);
    for(int i = 1; i < end; ++i)
        A[i] = -A[i - (i & -i)];
    for(int i = 1; i < end; i <<= 1)
        for(int j = 0; j < end; ++j)
            if(j & i)
                P[j] += P[j ^ i];
    bool flag = true;
    int e2 = end - 1;
    for(int i = 0; i < e2; ++i)
        if(P[i] >= eps) {
            flag = false;
            break;
        }
    if(flag) {
        FT ans = 0.0;
        for(int i = 0; i < e2; ++i)
            ans += A[i] / (P[i] - 1.0);
        printf("%.10lf\n", ans);
    } else
        puts("INF");
    return 0;
}
