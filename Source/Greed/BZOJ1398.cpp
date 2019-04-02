#include <algorithm>
#include <cstdio>
#include <cstring>
const int size = 1000005;
int add(int a, int b, int m) {
    a += b;
    return a < m ? a : a - m;
}
void build(int n, const char* A, char* B) {
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        char ci = A[add(i, k, n)],
             cj = A[add(j, k, n)];
        if(ci == cj)
            ++k;
        else {
            (ci < cj ? j : i) += k + 1;
            if(i == j)
                ++j;
            k = 0;
        }
    }
    int pos = std::min(i, j);
    memcpy(B, A + pos, n - pos);
    memcpy(B + n - pos, A, pos);
}
char A[size], B[size], C[size];
int main() {
    scanf("%s", A);
    int n = strlen(A);
    build(n, A, B);
    scanf("%s", A);
    build(n, A, C);
    if(strcmp(B, C))
        puts("No");
    else {
        puts("Yes");
        puts(B);
    }
    return 0;
}
