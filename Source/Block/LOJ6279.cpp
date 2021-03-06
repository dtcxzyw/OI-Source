#include <algorithm>
#include <cmath>
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
int A[size], B[320], C[size], n, bc;
int getL(int id) {
    return std::max(1, id * bc);
}
int getR(int id) {
    return std::min((id + 1) * bc - 1, n);
}
void rebuild(int id) {
    int l = getL(id), r = getR(id);
    memcpy(C + l, A + l, sizeof(int) * (r - l + 1));
    std::sort(C + l, C + r + 1);
}
int main() {
    n = read();
    bc = sqrt(n);
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(C + 1, A + 1, sizeof(int) * n);
    int maxb = n / bc;
    for(int i = 0; i <= maxb; ++i)
        std::sort(C + getL(i), C + getR(i) + 1);
    for(int i = 1; i <= n; ++i) {
        int op = read();
        int l = read();
        int r = read();
        int c = read();
        int lb = l / bc, rb = r / bc;
        if(op) {
            int ans = -1;
            if(lb == rb) {
                for(int i = l; i <= r; ++i) {
                    int val = A[i] + B[lb];
                    if(val < c)
                        ans = std::max(ans, val);
                }
            } else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i) {
                    int off = c - B[i], lp = getL(i),
                        rp = getR(i);
                    int pos =
                        std::lower_bound(
                            C + lp, C + rp + 1, off) -
                        C - 1;
                    if(pos >= lp) {
                        int val = C[pos] + B[i];
                        ans = std::max(ans, val);
                    }
                }
                for(int i = l; i < bbp; ++i) {
                    int val = A[i] + B[lb];
                    if(val < c)
                        ans = std::max(ans, val);
                }
                for(int i = ebp; i <= r; ++i) {
                    int val = A[i] + B[rb];
                    if(val < c)
                        ans = std::max(ans, val);
                }
            }
            printf("%d\n", ans);
        } else {
            if(lb == rb) {
                for(int i = l; i <= r; ++i)
                    A[i] += c;
                rebuild(lb);
            } else {
                int bb = (l - 1) / bc + 1,
                    eb = (r + 1) / bc - 1;
                int bbp = bb * bc, ebp = (eb + 1) * bc;
                for(int i = bb; i <= eb; ++i)
                    B[i] += c;
                for(int i = l; i < bbp; ++i)
                    A[i] += c;
                if(l < bbp)
                    rebuild(lb);
                for(int i = ebp; i <= r; ++i)
                    A[i] += c;
                if(ebp <= r)
                    rebuild(rb);
            }
        }
    }
    return 0;
}
