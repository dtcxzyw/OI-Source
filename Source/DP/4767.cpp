#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxV = 3005;
int A[maxV], S[maxV];
int calcW(int l, int r) {
    int mid = (l + r) >> 1;
    return ((S[r] - S[mid]) - (r - mid) * A[mid]) + ((mid - l) * A[mid] - (S[mid - 1] - S[l - 1]));
}
int f[maxV][maxV], k[maxV][maxV];
int main() {
    int v, p;
    scanf("%d%d", &v, &p);
    for (int i = 1; i <= v; ++i) {
        scanf("%d", &A[i]);
        S[i] = S[i - 1] + A[i];
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i <= v; ++i) {
        f[i][i] = 0;
        k[i][i] = i;
    }
    int maxOff = v - p;
    for (int off = 1; off <= maxOff; ++off) {
        int end = v - off;
        for (int i = 1; i <= end; ++i) {
            int j = i + off;
            for (int s = k[i][j - 1]; s <= k[i + 1][j]; ++s) {
                int val = f[i - 1][s - 1] + calcW(s, j);
                if (f[i][j] > val) {
                    f[i][j] = val;
                    k[i][j] = s;
                }
            }
        }
    }
    printf("%d\n", f[p][v]);
    return 0;
}
