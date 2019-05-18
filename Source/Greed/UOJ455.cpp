#include <algorithm>
#include <cstdio>
#include <queue>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int iabs(int x) {
    return x >= 0 ? x : -x;
}
const int size = 100005;
struct Rest {
    int y, w, c;
    bool operator<(const Rest& rhs) const {
        if(y != rhs.y)
            return y < rhs.y;
        return w > rhs.w;
    }
} A[size];
int X[size];
bool used[size];
struct Info {
    int rid, pid, dir, w;
    Info(int rid, int pid, int dir)
        : rid(rid), pid(pid), dir(dir),
          w(iabs(X[pid] - A[rid].y) + A[rid].w) {}
    bool operator<(const Info& rhs) const {
        return w > rhs.w;
    }
};
typedef long long Int64;
int nxt[size], pre[size];
void erase(int id) {
    nxt[pre[id]] = nxt[id];
    pre[nxt[id]] = pre[id];
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        X[i] = read();
    for(int i = 1; i <= m; ++i) {
        A[i].y = read();
        A[i].w = read();
        A[i].c = read();
    }
    // std::sort(A + 1, A + m + 1);
    std::priority_queue<Info> heap;
    int ptr = 0;
    for(int i = 1; i <= m; ++i) {
        while(ptr < n && X[ptr + 1] <= A[i].y)
            ++ptr;
        if(ptr)
            heap.emplace(i, ptr, -1);
        if(ptr < n)
            heap.emplace(i, ptr + 1, 1);
    }
    for(int i = 1; i <= n; ++i)
        pre[i] = i - 1, nxt[i] = i + 1;
    int rem = n;
    Int64 res = 0;
    while(heap.size()) {
        Info top = heap.top();
        heap.pop();
        if(A[top.rid].c > 0 && !used[top.pid]) {
            --A[top.rid].c, --rem, res += top.w;
            if(rem == 0)
                break;
            used[top.pid] = true;
            erase(top.pid);
        }
        int np = (top.dir == 1 ? nxt : pre)[top.pid];
        if(A[top.rid].c && np >= 1 && np <= n)
            heap.emplace(top.rid, np, top.dir);
    }
    if(rem)
        puts("-1");
    else
        printf("%lld\n", res);
    return 0;
}
