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
struct Block {
    int sum, pos;
    bool operator<(const Block& rhs) const {
        return sum > rhs.sum;
    }
} B[size];
int pre[size], nxt[size];
bool flag[size];
void del(int x) {
    if(x) {
        nxt[pre[x]] = nxt[x];
        pre[nxt[x]] = pre[x];
        flag[x] = true;
    }
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
        for(int i = b; i <= e; ++i) {
            if(A[i] > 0)
                res += A[i], ++cnt;
            else
                A[i] = -A[i];
            B[i].sum = A[i];
            B[i].pos = i;
            pre[i] = i - 1, nxt[i] = i + 1;
        }
        pre[b] = nxt[e] = 0;
        std::make_heap(B + b, B + e + 1);
        while(cnt > m && b <= e) {
            Block x = B[b];
            std::pop_heap(B + b, B + e + 1);
            --e;
            if(flag[x.pos])
                continue;
            --cnt;
            res -= x.sum;
            if(pre[x.pos] && nxt[x.pos]) {
                x.sum = A[x.pos] = A[pre[x.pos]] +
                    A[nxt[x.pos]] - A[x.pos];
                B[++e] = x;
                std::push_heap(B + b, B + e + 1);
                del(pre[x.pos]);
                del(nxt[x.pos]);
            } else {
                del(pre[x.pos]);
                del(nxt[x.pos]);
                del(x.pos);
            }
        }
        printf("%d\n", res);
    } else
        puts("0");
    return 0;
}
