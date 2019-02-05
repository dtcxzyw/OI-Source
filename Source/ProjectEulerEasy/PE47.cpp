#include <cstdio>
int main() {
    int last = -1, lcnt = 0;
    for(int i = 1;; ++i) {
        int pcnt = 0, ci = i;
        for(int j = 2; j * j <= ci; ++j)
            if(ci % j == 0) {
                ++pcnt;
                do
                    ci /= j;
                while(ci % j == 0);
            }
        if(ci != 1)
            ++pcnt;
        if(pcnt != last)
            last = pcnt, lcnt = 0;
        ++lcnt;
        if(pcnt == 4 && lcnt == 4) {
            printf("%d\n", i - 3);
            break;
        }
    }
    return 0;
}
