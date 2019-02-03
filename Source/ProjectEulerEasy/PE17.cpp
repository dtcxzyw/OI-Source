#include <cstdio>
int A[20] = { 0, 3, 3, 5, 4, 4, 3, 5, 5, 4,
              3, 6, 6, 8, 8, 7, 7, 9, 8, 8 };
int B[10] = { 0, 0, 6, 6, 5, 5, 5, 7, 6, 6 };
int count(int x) {
    if(x >= 100)
        return A[x / 100] + 7 + (x % 100 ? 3 : 0) +
            count(x % 100);
    if(x >= 20)
        return B[x / 10] + A[x % 10];
    return A[x];
}
int main() {
    int cnt = 11;
    for(int i = 1; i < 1000; ++i)
        cnt += count(i);
    printf("%d\n", cnt);
    return 0;
}
