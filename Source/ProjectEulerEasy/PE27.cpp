#include <cstdio>
const int size = 2100000;
bool flag[size + 5];
int main() {
    flag[1] = true;
    for(int i = 2; i <= size; ++i)
        if(!flag[i])
            for(int j = i * 2; j <= size; j += i)
                flag[j] = true;
    int maxc = 0, prod = 0;
    for(int a = -1000; a <= 1000; ++a) {
        for(int b = -1000; b <= 1000; ++b) {
            int n = 0;
            while(true) {
                int v = (n + a) * n + b;
                if(v > 0 && !flag[v])
                    ++n;
                else
                    break;
            }
            if(n > maxc)
                maxc = n, prod = a * b;
        }
    }
    printf("%d %d\n", maxc, prod);
    return 0;
}
