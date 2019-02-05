#include <cstdio>
int main() {
    int mcnt = 0, mi = 0;
    for(int i = 3; i <= 1000; ++i) {
        int cnt = 0;
        for(int j = 1; j <= i; ++j)
            for(int k = j; i - (j + k) >= k; ++k) {
                int l = i - (j + k);
                if(j * j + k * k == l * l)
                    ++cnt;
            }
        if(cnt > mcnt)
            mcnt = cnt, mi = i;
    }
    printf("%d %d\n", mi, mcnt);
    return 0;
}
