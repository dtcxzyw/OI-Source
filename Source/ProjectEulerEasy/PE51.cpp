#include <cstdio>
const int size = 1000000;
bool flag[size + 5];
int A[10];
int count(int i, int j, int icnt, bool show) {
    int res = 0;
    bool vis = false;
    for(int k = (j >> (icnt - 1)) & 1; k < 10; ++k) {
        int val = 0;
        for(int l = icnt - 1; l >= 0; --l)
            val = val * 10 + (j & (1 << l) ? k : A[l]);
        if(!flag[val]) {
            ++res;
            vis |= val == i;
            if(show)
                printf("%d\n", val);
        }
    }
    return vis ? res : -1;
}
int main() {
    flag[0] = flag[1] = true;
    for(int i = 2; i < size; ++i)
        if(!flag[i]) {
            for(int j = i * 2; j < size; j += i)
                flag[j] = true;
        }
    int b[10];
    b[0] = 1;
    for(int i = 1; i < 10; ++i)
        b[i] = b[i - 1] * 10;
    for(int i = 1; i < size; ++i)
        if(!flag[i]) {
            printf("check %d\n", i);
            int ci = i, icnt = 0;
            while(ci) {
                A[icnt++] = ci % 10;
                ci /= 10;
            }
            int end = 1 << icnt;
            for(int j = 1; j < end; ++j) {
                int res = count(i, j, icnt, false);
                printf("[%d]", res);
                if(res == 8) {
                    printf("\nfind %d\n", i);
                    count(i, j, icnt, true);
                    return 0;
                }
            }
            puts("");
        }
    return 0;
}
