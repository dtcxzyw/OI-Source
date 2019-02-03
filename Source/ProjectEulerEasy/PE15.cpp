#include <cstdio>
typedef long long Int64;
Int64 C[45][25];
int main() {
    C[0][0] = 1;
    for(int i = 1; i <= 40; ++i) {
        C[i][0] = 1;
        for(int j = 1; j <= 20; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    printf("%lld\n", C[40][20]);
    return 0;
}
