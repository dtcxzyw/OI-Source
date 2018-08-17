#include <algorithm>
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
int getOp() {
    int c;
    do
        c = getchar();
    while(c < 'A' || c > 'Z');
    return c;
}
int getRand() {
    static int seed = 3542;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 80005;
struct Node {
    int ls, rs, siz, pri, val;
} T[size];
void update(int id) {
    T[id].siz = T[T[id].ls].siz + T[T[id].rs].siz + 1;
}
int merge(int u, int v) {
    if(u && v) {
        if(T[u].pri < T[v].pri) {
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
void splitKey(int u, int k, int& x, int& y) {
    if(u) {
        if(T[u].val <= k) {
            x = u;
            splitKey(T[u].rs, k, T[u].rs, y);
        } else {
            y = u;
            splitKey(T[u].ls, k, x, T[u].ls);
        }
        update(u);
    } else
        x = y = 0;
}
void splitKth(int u, int k, int& x, int& y) {
    if(u) {
        int lsiz = T[T[u].ls].siz;
        if(k <= lsiz) {
            y = u;
            splitKth(T[u].ls, k, x, T[u].ls);
        } else {
            x = u;
            splitKth(T[u].rs, k - lsiz - 1, T[u].rs, y);
        }
        update(u);
    } else
        x = y = 0;
}
int erase(int root, int key) {
    int lt, rt;
    splitKey(root, key, lt, rt);
    int llt, lrt;
    splitKey(lt, key - 1, llt, lrt);
    return merge(llt, rt);
}
int rank(int u, int k) {
    if(u) {
        if(T[u].val < k)
            return rank(T[u].rs, k) + T[T[u].ls].siz + 1;
        else
            return rank(T[u].ls, k);
    }
    return 0;
}
int kth(int u, int k) {
    int lsiz = T[T[u].ls].siz;
    if(k <= lsiz)
        return kth(T[u].ls, k);
    if(k == lsiz + 1)
        return u;
    return kth(T[u].rs, k - lsiz - 1);
}
int A[size];
int build(int l, int r) {
    if(l <= r) {
        int m = (l + r) >> 1;
        int id = A[m];
        T[id].pri = getRand();
        T[id].val = m;
        T[id].siz = 1;
        T[id].ls = build(l, m - 1);
        T[id].rs = build(m + 1, r);
        update(id);
        return id;
    }
    return 0;
}
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i)
        A[i] = read();
    int mini = 1, maxi = n;
    int root = build(1, n);
    while(m--) {
        switch(getOp()) {
            case 'T': {
                int u = read();
                root = erase(root, T[u].val);
                T[u].val = --mini;
                root = merge(u, root);
                break;
            }
            case 'B': {
                int u = read();
                root = erase(root, T[u].val);
                T[u].val = ++maxi;
                root = merge(root, u);
                break;
            }
            case 'I': {
                int u = read();
                int t = read();
                if(t) {
                    int key = T[u].val;
                    int lt, rt;
                    splitKey(root, key, lt, rt);
                    int llt, lrt;
                    splitKey(lt, key - 1, llt, lrt);
                    int vlt, vrt;
                    if(t == -1) {
                        splitKth(llt, T[llt].siz - 1, vlt, vrt);
                        std::swap(T[lrt].val, T[vrt].val);
                        root = merge(vlt, merge(lrt, merge(vrt, rt)));
                    } else {
                        splitKth(rt, 1, vlt, vrt);
                        std::swap(T[lrt].val, T[vlt].val);
                        root =
                            merge(llt, merge(vlt, merge(lrt, vrt)));
                    }
                }
                break;
            }
            case 'A': {
                printf("%d\n", rank(root, T[read()].val));
                break;
            }
            case 'Q': {
                printf("%d\n", kth(root, read()));
                break;
            }
        }
    }
    return 0;
}
