#include <cmath>
#include <cstdio>
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
const int size = 50005;
int A[size], B[230];
int main() {
    int n = read();
    int bc = sqrt(n);
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i) {
        int op = read();
        int l = read();
        int r = read();
        int c = read();
        if(op)
            printf("%d\n", A[r] + B[r / bc]);
        else {
            int lb = l / bc, rb = r / bc;
            if(lb == rb)
                for(int i = l; i <= r; ++i)
                    A[i] += c;
            else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i)
                    B[i] += c;
                for(int i = l; i < bbp; ++i)
                    A[i] += c;
                for(int i = ebp; i <= r; ++i)
                    A[i] += c;
            }
        }
    }
    return 0;
}
