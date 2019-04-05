#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 100005;
int A[size];
bool cmp(int a, int b) {
    return a > b;
}
int main() {
    int n = read();
    int m = read();
    int rn = 0;
    for(int i = 1; i <= n; ++i) {
        int val = read();
        if(val) {
            if(rn == 0 || (val ^ A[rn]) < 0)
                A[++rn] = val;
            else
                A[rn] += val;
        }
    }
    int b = 1;
    while(A[b] < 0)
        ++b;
    int e = rn;
    while(A[e] < 0)
        --e;
    if(b <= e) {
        int res = 0, cnt = 0;
        for(int i = b; i <= e; ++i)
            if(A[i] > 0)
                res += A[i], ++cnt;
            else
                A[i] = -A[i];
        std::make_heap(A + b, A + e + 1, cmp);
        for(; cnt > m; --cnt) {
            res -= A[b];
            std::pop_heap(A + b, A + e + 1, cmp);
            --e;
        }
        printf("%d\n", res);
    } else
        puts("0");
    return 0;
}
