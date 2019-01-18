#include <algorithm>
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
const int size = 100005;
int A[size], B[320], n, bc;
int getL(int id) {
    return std::max(1, id * bc);
}
int getR(int id) {
    return std::min((id + 1) * bc - 1, n);
}
int solveBlock(int l, int r, int id, int c) {
    int res = 0;
    if(B[id]) {
        if(B[id] == c)
            res += r - l + 1;
        else {
            int old = B[id], bp = getL(id),
                ep = getR(id);
            for(int i = bp; i < l; ++i)
                A[i] = old;
            for(int i = r + 1; i <= ep; ++i)
                A[i] = old;
            for(int i = l; i <= r; ++i)
                A[i] = c;
            B[id] = 0;
        }
    } else {
        for(int i = l; i <= r; ++i)
            if(A[i] == c)
                ++res;
            else
                A[i] = c;
    }
    return res;
}
int main() {
    n = read();
    bc = sqrt(n);
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    for(int i = 1; i <= n; ++i) {
        int l = read();
        int r = read();
        int c = read();
        int lb = l / bc, rb = r / bc, res = 0;
        if(lb == rb)
            res = solveBlock(l, r, lb, c);
        else {
            int bb = (l - 1) / bc + 1,
                eb = (r + 1) / bc - 1;
            int bbp = bb * bc, ebp = (eb + 1) * bc;
            for(int i = bb; i <= eb; ++i) {
                if(B[i]) {
                    if(B[i] == c)
                        res += getR(i) - getL(i) + 1;
                    else
                        B[i] = c;
                } else {
                    int bp = getL(i), ep = getR(i);
                    for(int j = bp; j <= ep; ++j)
                        if(A[j] == c)
                            ++res;
                        else
                            A[j] = c;
                    B[i] = c;
                }
            }
            if(l < bbp)
                res += solveBlock(l, bbp - 1, lb, c);
            if(ebp <= r)
                res += solveBlock(ebp, r, rb, c);
        }
        printf("%d\n", res);
    }
    return 0;
}
