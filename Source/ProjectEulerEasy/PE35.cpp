#include <cstdio>
const int size = 1000000;
bool flag[size + 5];
int rotate(int x) {
    int val[10], icnt = 0;
    while(x) {
        val[icnt++] = x % 10;
        x /= 10;
    }
    val[icnt] = val[0];
    int res = 0;
    for(int i = icnt; i >= 1; --i)
        res = res * 10 + val[i];
    return res;
}
int main() {
    for(int i = 2; i < size; ++i)
        if(!flag[i])
            for(int j = i * 2; j < size; j += i)
                flag[j] = true;
    int res = 0;
    for(int i = 2; i < size; ++i)
        if(!flag[i]) {
            int ci = i;
            while(ci) {
                int v = ci % 10;
                if(v == 0)
                    goto err;
                ci /= 10;
            }
            ci = i;
            while(true) {
                ci = rotate(ci);
                if(ci == i)
                    break;
                if(flag[ci])
                    goto err;
            }
            printf("%d\n", i);
            ++res;
        err : {}
        }
    printf("%d\n", res);
    return 0;
}
