#include <algorithm>
#include <cstdio>
#include <cstring>
int iabs(int x) {
    return x >= 0 ? x : -x;
}
int A[15], B[15];
int foo(int n) {
    for(int i = 1; i <= n; ++i)
        A[i] = i;
    int cnt = 0;
    do {
        int a = 0;
        for(int i = 1; i <= n; ++i) {
            a += iabs(i - A[i]);
        }
        memcpy(B, A, sizeof(A));
        int b = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j < n; ++j)
                if(B[j] > B[j + 1]) {
                    std::swap(B[j], B[j + 1]);
                    ++b;
                }
        }
        if(b * 2 == a)
            ++cnt;
    } while(std::next_permutation(A + 1, A + n + 1));
    return cnt;
}
int main() {
    for(int i = 1; i <= 10; ++i)
        printf("%d %d\n", i, foo(i));
    return 0;
}
