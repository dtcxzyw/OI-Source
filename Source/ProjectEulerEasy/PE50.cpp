#include <cstdio>
const int size = 1000000;
bool flag[size + 5];
int p[size];
int main() {
    int pcnt = 0;
    flag[0] = flag[1] = true;
    for(int i = 2; i < size; ++i)
        if(!flag[i]) {
            p[++pcnt] = i;
            for(int j = i * 2; j < size; j += i)
                flag[j] = true;
        }
    int res = 0, mcnt = 1;
    for(int i = 1; i <= pcnt; ++i) {
        int sum = 0;
        for(int j = i; j <= pcnt; ++j) {
            sum += p[j];
            if(sum >= size)
                break;
            if(!flag[sum]) {
                int cnt = j - i + 1;
                if(cnt > mcnt)
                    res = sum, mcnt = cnt;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}
