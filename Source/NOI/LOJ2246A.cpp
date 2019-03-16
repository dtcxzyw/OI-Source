#include <cstdio>
#include <cstring>
const int size = 1000005, mod = 1000000007;
typedef long long Int64;
char buf[size];
int p[size][20], nxt[size], d[size];
int foo() {
    scanf("%s", buf);
    int len = strlen(buf);
    Int64 res = 1;
    d[1] = 1;
    for(int i = 1, j = 0; i <= len; ++i) {
        while(j && buf[i] != buf[j])
            j = nxt[j];
        if(buf[i] == buf[j])
            ++j;
        int k = i + 1;
        nxt[k] = j;
        d[k] = d[nxt[k]] + 1;
        p[k][0] = nxt[k];
        for(int l = 1; l < 20; ++l)
            p[k][l] = p[p[k][l - 1]][l - 1];
        int cur = nxt[k];
        for(int l = 19; l >= 0; --l)
            if(p[cur][l] * 2 > k)
                cur = p[cur][l];
        int num = d[cur] + (cur * 2 <= k);
        res = res * num % mod;
    }
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", foo());
    return 0;
}
