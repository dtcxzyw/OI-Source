//3369
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
int getRand() {
    static int seed = 347;
    return seed = seed * 48271LL % 2147483647;
}
const int size = 100005;
struct Node {
    int val, pri, ls, rs, siz;
} T[size];
int newNode(int val) {
    static int cnt = 0;
    int id = ++cnt;
    T[id].val = val;
    T[id].pri = getRand();
    T[id].ls = T[id].rs = 0;
    T[id].siz = 1;
    return id;
}
void update(int u) {
    T[u].siz = T[T[u].ls].siz + T[T[u].rs].siz + 1;
}
void split(int u, int k, int &x, int &y) {
    if (u) {
        if (T[u].val < k) {
            x = u;
            split(T[u].rs, k, T[u].rs, y);
        } else {
            y = u;
            split(T[u].ls, k, x, T[u].ls);
        }
        update(u);
    } else
        x = y = 0;
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
int kth(int u, int rk) {
    int lsiz = T[T[u].ls].siz;
    if (rk <= lsiz) return kth(T[u].ls, rk);
    if (rk == lsiz + 1) return T[u].val;
    return kth(T[u].rs, rk - lsiz - 1);
}
int main() {
    int n = read(), root = 0;
    while (n--) {
        switch (read()) {
            case 1: {
                int key = read();
                int node = newNode(key);
                int x = 0, y = 0;
                split(root, key, x, y);
                root = merge(x, merge(node, y));
            } break;
            case 2: {
                int key = read();
                int lt = 0, rt = 0, rlt = 0, rrt = 0;
                split(root, key, lt, rt);
                split(rt, key + 1, rlt, rrt);
                if (rlt) rlt = merge(T[rlt].ls, T[rlt].rs);
                root = merge(lt, merge(rlt, rrt));
            } break;
            case 3: {
                int lt = 0, rt = 0;
                split(root, read(), lt, rt);
                printf("%d\n", T[lt].siz + 1);
                root = merge(lt, rt);
            } break;
            case 4: {
                printf("%d\n", kth(root, read()));
            } break;
            case 5: {
                int lt = 0, rt = 0;
                split(root, read(), lt, rt);
                int u = lt;
                while (T[u].rs) u = T[u].rs;
                printf("%d\n", T[u].val);
                root = merge(lt, rt);
            } break;
            case 6: {
                int lt = 0, rt = 0;
                split(root, read() + 1, lt, rt);
                int u = rt;
                while (T[u].ls) u = T[u].ls;
                printf("%d\n", T[u].val);
                root = merge(lt, rt);
            } break;
        }
    }
    return 0;
}
