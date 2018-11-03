#include <cstdio>
#include <cstring>
int A[6], fac[13];
int solve(int len, int base = 12) {
    int ans = fac[base / len];
    for(int i = 0; i < 6; ++i) {
        int c = A[i] / len, d = A[i] % len;
        if(d)
            return 0;
        ans /= fac[c];
    }
    return ans;
}
int foo() {
    memset(A, 0, sizeof(A));
    for(int i = 0; i < 12; ++i) {
        int col;
        scanf("%d", &col);
        ++A[col - 1];
    }
    int ans = solve(1) + 3 * solve(2) + 8 * solve(3) +
        6 * solve(4);
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 6; ++j) {
            --A[i], --A[j];
            if(A[i] >= 0 && A[j] >= 0)
                ans += 6 * solve(2, 10);
            ++A[i], ++A[j];
        }
    return ans / 24;
}
int main() {
    fac[0] = 1;
    for(int i = 1; i <= 12; ++i)
        fac[i] = fac[i - 1] * i;
    int t;
    scanf("%d", &t);
    while(t--)
        printf("%d\n", foo());
    return 0;
}
