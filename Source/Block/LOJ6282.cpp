#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
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
const int size = 200005;
int A[size], bc, cnt;
int getL(int id) {
    return std::max(1, id * bc);
}
int getR(int id) {
    return std::min((id + 1) * bc - 1, cnt);
}
std::vector<int> B[450];
int rebuild() {
    bc = sqrt(cnt);
    int maxb = cnt / bc;
    for(int i = 0; i <= maxb; ++i) {
        int lp = getL(i), rp = getR(i);
        B[i].assign(A + lp, A + rp + 1);
    }
    return maxb;
}
int main() {
    int n = read();
    int delta = sqrt(n);
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    bc = delta, cnt = n;
    int last = 0, maxb = rebuild();
    for(int i = 1; i <= n; ++i) {
        int op = read();
        int l = read();
        int r = read();
        int c = read();
        if(op) {
            for(int i = 0; i <= maxb; ++i) {
                if(r > B[i].size())
                    r -= B[i].size();
                else {
                    printf("%d\n", B[i][r - 1]);
                    break;
                }
            }
        } else {
            for(int i = 0; i <= maxb; ++i) {
                if(l > B[i].size())
                    l -= B[i].size();
                else {
                    B[i].insert(B[i].begin() + l - 1,
                                r);
                    break;
                }
            }
            if(i - last > delta) {
                last = i;
                int id = 1;
                for(int i = 0; i <= maxb; ++i) {
                    memcpy(A + id, B[i].data(),
                           sizeof(int) * B[i].size());
                    id += B[i].size();
                }
                maxb = rebuild();
            }
        }
    }
    return 0;
}
