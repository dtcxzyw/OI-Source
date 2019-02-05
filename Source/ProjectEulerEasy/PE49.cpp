#include <algorithm>
#include <cstdio>
const int size = 10000;
bool flag[size];
int sort(int x) {
    int A[5], icnt = 0;
    while(x) {
        A[icnt++] = x % 10;
        x /= 10;
    }
    std::sort(A, A + icnt);
    int res = 0;
    for(int i = 0; i < icnt; ++i)
        res = res * 10 + A[i];
    return res;
}
int main() {
    for(int i = 2; i < size; ++i)
        if(!flag[i])
            for(int j = i * 2; j < size; j += i)
                flag[j] = true;
    for(int i = 1000; i < size; ++i)
        if(!flag[i])
            for(int j = 1; i + j * 2 < size; ++j)
                if(!flag[i + j] && !flag[i + j + j]) {
                    int va = sort(i), vb = sort(i + j),
                        vc = sort(i + j + j);
                    if(va == vb && vb == vc)
                        printf("%d %d %d\n", i, i + j,
                               i + j + j);
                }
    return 0;
}
