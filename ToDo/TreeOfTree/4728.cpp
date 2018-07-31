//TODO:complete
//http://www.docin.com/p-649133451.html
//http://vfleaking.blog.163.com/blog/static/1748076342013127965652/
#include <cstdio>
#include <map>
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
    while (c != 'Q' && c != 'M' && c != 'I');
    return c;
}
int getRand() {
    static int seed = 235;
    return seed = seed * 48271LL % 2147483647;
}
const int maxm = 70001, size = maxm + 5;
struct Node {
    int val, ls, rs, siz, pri, p;
} T[size * 200];
std::vector<int> pool;
int allocNode() {
    static int cnt = 0;
    if (pool.empty())
        return ++cnt;
    else {
        int id = pool.back();
        pool.pop_back();
        return id;
    }
}
void freeNode(int id) {
    pool.push_back(id);
}
int newNode(int val) {
    int id = allocNode();
    T[id].val = val;
    T[id].ls = T[id].rs = 0;
    T[id].siz = 1;
    T[id].pri = getRand();
    T[id].p = 0;
    return id;
}
void update(int id) {
    T[T[id].ls].p = T[T[id].rs].p = id;
    T[id].siz = T[T[id].ls].siz + T[T[id].rs].siz + 1;
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
void split(int u, int k, int &x, int &y) {
    if (u) {
        T[u].p = 0;
        int lsiz = T[T[u].ls].siz;
        if (k <= lsiz) {
            y = u;
            split(T[u].ls, k, x, T[u].ls);
        } else {
            x = u;
            split(T[u].rs, k - lsiz - 1, T[u].rs, y);
        }
        update(u);
    } else
        x = y = 0;
}
void insertT(int &root, int k, int id) {
    int lt, rt;
    if (k > 1)
        split(root, k - 1, lt, rt);
    else
        lt = 0, rt = root;
    root = merge(lt, merge(id, rt));
}
void eraseT(int &root, int k) {
    int lt, rt;
    split(root, k, lt, rt);
    int llt, lrt;
    if (k > 1)
        split(lt, k - 1, llt, lrt);
    else
        llt = 0, lrt = lt;
    root = merge(llt, rt);
    freeNode(lrt);
}
int kth(int u, int k) {
    int lsiz = T[T[u].ls].siz;
    if (k <= lsiz) return kth(T[u].ls, k);
    if (k == lsiz + 1) return u;
    return kth(T[u].rs, k - lsiz - 1);
}
int rank(int id) {
    int res = 0;
    bool isRight = true;
    while (id) {
        if (isRight) res += T[T[id].ls].siz + 1;
        isRight = (T[T[id].p].rs == id);
        id = T[id].p;
    }
    return res;
}
int rt[size << 2];
std::map<int, int> tid[size << 2];
void insert(int l, int r, int id, int p, int pid, int rk) {
    int &root = rt[id];
    insertT(root, rk, tid[id][pid] = newNode(0));
    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m) {
            insert(l, m, id << 1, p, pid, rk);
        } else {
            insert(m + 1, r, id << 1 | 1, p, pid, rk);
        }
    }
}
void erase(int l, int r, int id, int p, int pid, int rk) {
    int root = rt[id];
}
int query(int &id, int nl, int nr) {
}
int query(int l, int r, int id, int k, int nl, int nr) {
    if (l == r)
        return l;
    else {
        int lsiz = query(rt[id << 1], nl, nr);
        int m = (l + r) >> 1;
        if (k <= lsiz) return query(l, m, id << 1, k, nl, nr);
        return query(m + 1, r, id << 1 | 1, k - lsiz, nl, nr);
    }
}
int main() {
    printf("%d\n", sizeof(T) >> 20);
    int n = read(), root = 0;
    for (int i = 1; i <= n; ++i) {
        int x = read() + 1;
        int id = newNode(x);
        insert(1, maxm, 1, x, id, i);
        root = merge(root, id);
    }
    int m = read(), lastAns = 0, cnt = n;
    while (m--) {
        int op = getOp();
        int a = read() ^ lastAns;
        int b = read() ^ lastAns;
        switch (op) {
            case 'Q': {
                int k = read() ^ lastAns;
                printf("%d\n", lastAns = query(1, maxm, 1, k, a, b) - 1);
                break;
            }
            case 'M': {
                int id = kth(root, a);
                int old = T[id].val;
                T[id].val = b + 1;
                erase(1, maxm, 1, old, id, a);
                insert(1, maxm, 1, b + 1, id, a);
                break;
            }
            case 'I': {
                int id = newNode(b);
                insertT(root, a, id);
                insert(1, maxm, 1, b + 1, id, a);
                break;
            }
        }
    }
    return 0;
}
