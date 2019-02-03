#include <algorithm>
#include <cstdio>
int main() {
    int res = 0;
    for(int i = 100; i < 1000; ++i)
        for(int j = i; j < 1000; ++j) {
            int val = i * j;
            int b[6];
            for(int k = 0; k < 6; ++k) {
                b[k] = val % 10;
                val /= 10;
            }
            if(b[0] == b[5] && b[1] == b[4] &&
               b[2] == b[3])
                res = std::max(res, i * j);
        }
    printf("%d\n", res);
    return 0;
}
