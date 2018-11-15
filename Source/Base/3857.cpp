#include <cstdio>
typedef long long Mask;
Mask base[51];
int main() {
    int n, m, bsiz = 0;
    scanf("%d%d", &n, &m);
    while(m--) {
        Mask x = 0;
        int c;
        do
            c = getchar();
        while(c != 'X' && c != 'O');
        while(c == 'X' || c == 'O') {
            x = x << 1 | (c == 'O');
            c = getchar();
        }
        for(int i = 50; i >= 0; --i)
            if(x & (1LL << i)) {
                if(base[i])
                    x ^= base[i];
                else {
                    base[i] = x, ++bsiz;
                    break;
                }
            }
    }
    int res = (1LL << bsiz) % 2008;
    printf("%d\n", res);
    return 0;
}
