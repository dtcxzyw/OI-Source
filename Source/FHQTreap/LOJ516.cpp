#include <algorithm>
#include <cstdio>
#include <map>
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
int getRandom() {
    static int seed = 15455;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 100005, inf = 2147483647;
struct Node {
    int lc, rc, pri, siz, mind, maxv, minv;
} T[size];
#define ls (T[u].lc)
#define rs (T[u].rc)
void initNode(int u) {
    T[u].mind = inf;
    T[u].minv = T[u].maxv = u;
    T[u].siz = 1;
}
void update(int u) {
    T[u].siz = T[ls].siz + T[rs].siz + 1;
    T[u].mind =
        std::min(std::min(T[ls].mind, T[rs].mind),
                 std::min(ls ? u - T[ls].maxv : inf,
                          rs ? T[rs].minv - u : inf));
    T[u].maxv = (rs ? T[rs].maxv : u);
    T[u].minv = (ls ? T[ls].minv : u);
}
int merge(int u, int v) {
    if(u && v) {
        if(T[u].pri < T[v].pri) {
            T[u].rc = merge(T[u].rc, v);
            update(u);
            return u;
        } else {
            T[v].lc = merge(u, T[v].lc);
            update(v);
            return v;
        }
    }
    return u | v;
}
void split(int u, int k, int& x, int& y) {
    if(u) {
        if(u < k) {
            x = u;
            split(T[u].rc, k, T[u].rc, y);
        } else {
            y = u;
            split(T[u].lc, k, x, T[u].lc);
        }
        update(u);
    } else
        x = y = 0;
}
int insert(int root, int x) {
    int lt, rt;
    split(root, x, lt, rt);
    return merge(lt, merge(x, rt));
}
int dst;
void insertTree(int u) {
    if(u) {
        int lc = ls, rc = rs;
        insertTree(lc);
        T[u].lc = T[u].rc = 0;
        initNode(u);
        dst = insert(dst, u);
        insertTree(rc);
    }
}
int mergeTree(int u, int v) {
    if(T[u].siz > T[v].siz)
        std::swap(u, v);
    dst = v;
    insertTree(u);
    return dst;
}
std::map<int, int> rid;
typedef std::map<int, int>::iterator IterT;
std::pair<int, int> A[size];
int build(int l, int r) {
    if(l > r)
        return 0;
    if(l == r)
        return A[l].second;
    else {
        int m = (l + r) >> 1;
        int id = A[m].second;
        T[id].lc = build(l, m - 1);
        T[id].rc = build(m + 1, r);
        update(id);
        return id;
    }
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        A[i].first = read();
        A[i].second = i;
    }
    std::sort(A + 1, A + n + 1);
    T[0].mind = inf;
    for(int i = 1; i <= n; ++i) {
        T[i].pri = getRandom();
        initNode(i);
    }
    A[n + 1].first = getRandom();
    int l = 1, res = inf;
    for(int i = 1; i <= n; ++i) {
        if(A[i].first != A[i + 1].first) {
            int rt = build(l, i);
            rid[A[i].first] = rt;
            res = std::min(res, T[rt].mind);
            l = i + 1;
        }
    }
    while(m--) {
        int x = read();
        int y = read();
        if(res != 1 && x != y) {
            IterT rx = rid.find(x);
            if(rx != rid.end()) {
                int& ry = rid[y];
                if(ry) {
                    ry = mergeTree(ry, rx->second);
                    res = std::min(res, T[ry].mind);
                } else
                    ry = rx->second;
                rid.erase(rx);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
