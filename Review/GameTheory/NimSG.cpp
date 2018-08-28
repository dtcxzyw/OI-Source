#include <cstdio>
#include <cstring>
const int size = 25;
int SG[size];
int getSG(int x) {
    if(SG[x] == -1) {
        bool flag[size] = {};
        for(int i = 0; i < x; ++i)
            flag[getSG(i)] = true;
        for(int i = 0; i <= x; ++i)
            if(!flag[i]) {
                SG[x] = i;
                break;
            }
    }
    return SG[x];
}
int main() {
    memset(SG, -1, sizeof(SG));
    for(int i = 0; i <= 20; ++i)
        printf("SG(%d)=%d\n", i, getSG(i));
    return 0;
}
