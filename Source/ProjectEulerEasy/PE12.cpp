#include <cstdio>
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1, x = 1;; ++i, x += i) {
        int cnt = 1, nx = x;
        for(int j = 2; j * j <= nx; ++j)
            if(nx % j == 0) {
                int pc = 1;
                do
                    nx /= j, ++pc;
                while(nx % j == 0);
                cnt *= pc;
            }
        if(nx != 1)
            cnt *= 2;
        if(cnt > n) {
            printf("%d\n", x);
            break;
        }
    }
    return 0;
}
