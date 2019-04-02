#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 4000005;
int fa[size / 2];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void build(const char* S, int n, int* Z) {
    Z[0] = n;
    int L = 0, R = 0;
    for(int i = 1; i < n; ++i) {
        if(i > R) {
            L = R = i;
            while(S[R - L] == S[R])
                ++R;
            Z[i] = R - L;
            --R;
        } else {
            if(Z[i - L] < R - i + 1)
                Z[i] = Z[i - L];
            else {
                L = i;
                while(S[R - L] == S[R])
                    ++R;
                Z[i] = R - L;
                --R;
            }
        }
    }
}
char A[size], B[size];
int ZA[size], ZB[size];
int main() {
    int n;
    scanf("%d%s%s", &n, A, B);
    A[n] = B[n] = '#';
    memcpy(A + n + 1, B, n);
    memcpy(B + n + 1, A, n);
    build(A, 2 * n + 1, ZA);
    build(B, 2 * n + 1, ZB);
    for(int i = 1; i <= n; ++i)
        fa[i] = i;
    int ans = 0, off = n + 1;
    for(int i = 1; i <= n; ++i) {
        int x = ZA[i + off];
        for(int j = find(x); j >= 1;) {
            int val = ZB[j + off];
            if(val >= i) {
                ans = std::max(ans, i + j);
                break;
            } else {
                fa[j] = find(j - 1);
                j = fa[j];
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
