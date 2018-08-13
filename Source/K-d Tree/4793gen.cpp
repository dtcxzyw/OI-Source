#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
const int size = 2 * 200005;
int A[size], B[size];
int main() {
    srand(time(0));
    freopen("input.txt", "w", stdout);
    int n = 200000;
    printf("%d\n", n);
    int n2 = n * 2;
    for (int i = 0; i < n2; ++i) A[i] = B[i] = i;
    std::random_shuffle(A, A + n2);
    std::random_shuffle(B, B + n2);
    int cntA = 0, cntB = 0;
    for (int i = 0; i < n; ++i) {
        int x1 = A[cntA++];
        int y1 = B[cntB++];
        int x2 = A[cntA++];
        int y2 = B[cntB++];
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);
        printf("%d %d %d %d\n", x1, y1, x2, y2);
    }
    return 0;
}
