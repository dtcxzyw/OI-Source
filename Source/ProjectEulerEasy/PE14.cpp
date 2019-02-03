#include <cstdio>
int main() {
    int mx = 1, mcnt = 1;
    for(int i = 1; i < 1000000; ++i) {
        long long x = i;
        int cnt = 1;
        while(x != 1) {
            if(x & 1)
                x = 3 * x + 1;
            else
                x >>= 1;
            ++cnt;
        }
        if(cnt > mcnt)
            mcnt = cnt, mx = i;
    }
    printf("%d %d\n", mx, mcnt);
    return 0;
}
