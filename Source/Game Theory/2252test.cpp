#include <cstdio>
#include <cstring>
const int size = 21;
int sg[size][size];
int SG(int a, int b) {
    if(a == 0 && b == 0)
        return 0;
    if(sg[a][b] == -1) {
        bool flag[1000] = {};
        for(int i = 1; i <= a; ++i)
            flag[SG(a - i, b)] = true;
        for(int i = 1; i <= b; ++i)
            flag[SG(a, b - i)] = true;
        for(int i = 1; i <= a && i <= b; ++i)
            flag[SG(a - i, b - i)] = true;
        for(int i = 0; i < 1000; ++i)
            if(!flag[i]) {
                sg[a][b] = i;
                break;
            }
    }
    return sg[a][b];
}
int main() {
    memset(sg, -1, sizeof(sg));
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            printf("%d ", SG(i, j));
        }
        puts("");
    }
    for(int i = 0; i < size; ++i)
        for(int j = i; j < size; ++j)
            if(SG(i, j) == 0)
                printf("%d %d\n", i, j);
    return 0;
}
