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
const int size = 100005, sqsiz = 320, mod = 10007;
int A[size], C[sqsiz], D[sqsiz], n, bc;
int getL(int id) {
    return std::max(1, id * bc);
}
int getR(int id) {
    return std::min((id + 1) * bc - 1, n);
}
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
void pushMul(int id) {
    if(C[id] != 1) {
        int lp = getL(id), rp = getR(id);
        for(int i = lp; i <= rp; ++i)
            A[i] = A[i] * C[id] % mod;
        C[id] = 1;
    }
}
void solveBlockAdd(int l, int r, int id, int c) {
    pushMul(id);
    for(int i = l; i <= r; ++i)
        A[i] = add(A[i], c);
}
void solveAdd(int l, int r, int c) {
    if(c == 0)
        return;
    int lb = l / bc, rb = r / bc;
    if(lb == rb)
        solveBlockAdd(l, r, lb, c);
    else {
        int bb = (l - 1) / bc + 1,
            eb = (r + 1) / bc - 1;
        int bbp = bb * bc, ebp = (eb + 1) * bc;
        for(int i = bb; i <= eb; ++i)
            D[i] = add(D[i], c);
        if(l < bbp)
            solveBlockAdd(l, bbp - 1, lb, c);
        if(ebp <= r)
            solveBlockAdd(ebp, r, rb, c);
    }
}
void pushAdd(int id) {
    if(D[id]) {
        pushMul(id);
        int lp = getL(id), rp = getR(id);
        for(int i = lp; i <= rp; ++i)
            A[i] = add(A[i], D[id]);
        D[id] = 0;
    }
}
void solveBlockMul(int l, int r, int id, int c) {
    pushAdd(id);
    int sum = 0;
    for(int i = l; i <= r; ++i) {
        sum = add(sum, A[i]);
        A[i] = A[i] * c % mod;
    }
}
void solveMul(int l, int r, int c) {
    if(c == 1)
        return;
    int lb = l / bc, rb = r / bc;
    if(lb == rb)
        solveBlockMul(l, r, lb, c);
    else {
        int bb = (l - 1) / bc + 1,
            eb = (r + 1) / bc - 1;
        int bbp = bb * bc, ebp = (eb + 1) * bc;
        for(int i = bb; i <= eb; ++i) {
            C[i] = C[i] * c % mod;
            D[i] = D[i] * c % mod;
        }
        if(l < bbp)
            solveBlockMul(l, bbp - 1, lb, c);
        if(ebp <= r)
            solveBlockMul(ebp, r, rb, c);
    }
}
int main() {
    n = read();
    bc = sqrt(n);
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int maxb = n / bc;
    for(int i = 0; i <= maxb; ++i)
        C[i] = 1;
    for(int i = 1; i <= n; ++i) {
        int op = read();
        int l = read();
        int r = read();
        int c = read();
        switch(op) {
            case 0:
                solveAdd(l, r, c);
                break;
            case 1:
                solveMul(l, r, c);
                break;
            case 2:
                printf("%d\n",
                       (A[r] * C[r / bc] + D[r / bc]) %
                           mod);
                break;
        }
    }
    return 0;
}
