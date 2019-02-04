#include <cstdio>
int mat[1005][1005];
const int d[4][2] = { { 0, 1 },
                      { 1, 0 },
                      { 0, -1 },
                      { -1, 0 } };
int main() {
    int n;
    scanf("%d", &n);
    int cx = (n + 1) / 2, cy = (n + 1) / 2, dir = 0;
    for(int i = 1; i <= n * n; ++i) {
        mat[cx][cy] = i;
        int ndir = (dir + 1) % 4;
        if(i != 1 &&
           !mat[cx + d[ndir][0]][cy + d[ndir][1]])
            dir = ndir;
        cx += d[dir][0], cy += d[dir][1];
    }
    long long sum = 0;
    for(int i = 1; i <= n; ++i)
        sum += mat[i][i] + mat[n + 1 - i][i];
    printf("%lld\n", sum - 1);
    // A114254 1 + 10*n^2 + (16*n^3 + 26*n)/3
    long long ni = (n - 1) / 2;
    printf("%lld\n", 1 + 10 * ni * ni +
               (16 * ni * ni * ni + 26 * ni) / 3);
    return 0;
}
