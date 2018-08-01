#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
int getOp() {
    int c;
    do
        c = getchar();
    while (c != 'M' && c != 'A');
    return c;
}
int getRand() {
    static int seed = 2634;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 1000005, blockSize = 1005;
struct Node {
    int val, ls, rs, pri, siz;
} T[size];
std::vector<int> pool;
int allocNode() {
    static int cnt = 0;
    if (pool.size()) {
        int id = pool.back();
        pool.pop_back();
        return id;
    }
    return ++cnt;
}
void freeNode(int id) {
    pool.push_back(id);
}
int newNode(int val) {
    int id = allocNode();
    T[id].val = val;
    T[id].ls = T[id].rs = 0;
    T[id].pri = getRand();
    T[id].siz = 1;
    return id;
}
void update(int u) {
    T[u].siz = T[T[u].ls].siz + T[T[u].rs].siz + 1;
}
int merge(int u, int v) {
    if (u && v) {
        if (T[u].pri < T[v].pri) {
            T[u].rs = merge(T[u].rs, v);
            update(u);
            return u;
        } else {
            T[v].ls = merge(u, T[v].ls);
            update(v);
            return v;
        }
    }
    return u | v;
}
void split(int u, int key, int &x, int &y) {
    if (u) {
        if (T[u].val < key) {
            x = u;
            split(T[u].rs, key, T[u].rs, y);
        } else {
            y = u;
            split(T[u].ls, key, x, T[u].ls);
        }
        update(u);
    } else
        x = y = 0;
}
void insert(int &root, int val) {
    int lt, rt;
    split(root, val, lt, rt);
    root = merge(lt, merge(newNode(val), rt));
}
void erase(int &root, int val) {
    int lt, rt, rlt, rrt;
    split(root, val, lt, rt);
    split(rt, val + 1, rlt, rrt);
    root = merge(lt, merge(merge(T[rlt].ls, T[rlt].rs), rrt));
    freeNode(rlt);
}
int count(int &root, int key) {
    int lt, rt;
    split(root, key, lt, rt);
    int res = T[rt].siz;
    root = merge(lt, rt);
    return res;
}
int A[size], root[blockSize] = {}, offset[blockSize] = {};
void add(int bid, int id, int w) {
    erase(root[bid], A[id]);
    A[id] += w;
    insert(root[bid], A[id]);
}
int main() {
    int n = read();
    int bsiz = sqrt(n);
    int q = read();
    int cur = 0, mod = 1;
    for (int i = 1; i <= n; ++i) {
        A[i] = read();
        insert(root[cur], A[i]);
        if (++mod == bsiz) mod = 0, ++cur;
    }
    while (q--) {
        int op = getOp();
        int l = read();
        int r = read();
        int w = read();
        int lb = l / bsiz, rb = r / bsiz;
        int end = std::min((lb + 1) * bsiz - 1, n);
        int beg = std::max(1, rb * bsiz);
        if (op == 'M') {
            if (lb == rb) {
                for (int i = l; i <= r; ++i) add(lb, i, w);
            } else {
                for (int i = l; i <= end; ++i) add(lb, i, w);
                for (int i = lb + 1; i < rb; ++i) offset[i] += w;
                for (int i = beg; i <= r; ++i) add(rb, i, w);
            }
        } else {
            int cnt = 0;
            if (lb == rb) {
                int bw = w - offset[lb];
                for (int i = l; i <= r; ++i) cnt += A[i] >= bw;
            } else {
                int lbw = w - offset[lb];
                for (int i = l; i <= end; ++i) cnt += A[i] >= lbw;
                for (int i = lb + 1; i < rb; ++i) cnt += count(root[i], w - offset[i]);
                int rbw = w - offset[rb];
                for (int i = beg; i <= r; ++i) cnt += A[i] >= rbw;
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}
