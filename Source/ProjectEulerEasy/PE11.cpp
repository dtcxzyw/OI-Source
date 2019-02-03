#include <algorithm>
#include <cstdio>
int A[40][40];
int main() {
    for(int i = 5; i < 25; ++i)
        for(int j = 5; j < 25; ++j)
            scanf("%d", &A[i][j]);
    int res = 0;
    for(int i = 5; i < 25; ++i)
        for(int j = 5; j < 25; ++j) {
            int valA = 1, valB = 1, valC = 1, valD = 1;
            for(int k = 0; k < 4; ++k) {
                valA *= A[i][j + k];
                valB *= A[i + k][j];
                valC *= A[i + k][j + k];
                valD *= A[i + k][j - k];
            }
            res = std::max(
                res, std::max(std::max(valA, valB),
                              std::max(valC, valD)));
        }
    printf("%d\n", res);
    return 0;
}
