#include <algorithm>
#include <cstdio>
#include <set>
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
const int size = 100005;
struct Node {
    int p, c[2];
} T[size];
int dep[size << 2], root = 0;
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
#define srt 1, siz, 1
void push(int id) {
    if(dep[id]) {
        dep[id << 1] += dep[id];
        dep[id << 1 | 1] += dep[id];
        dep[id] = 0;
    }
}
void reset(int l, int r, int id, int p, int k) {
    if(l == r)
        dep[id] = k;
    else {
        push(id);
        int m = (l + r) >> 1;
        if(p <= m)
            reset(ls, p, k);
        else
            reset(rs, p, k);
    }
}
void modify(int l, int r, int id, int nl, int nr,
            int k) {
    if(nl <= l && r <= nr)
        dep[id] += k;
    else {
        push(id);
        int m = (l + r) >> 1;
        if(nl <= m)
            modify(ls, nl, nr, k);
        if(m < nr)
            modify(rs, nl, nr, k);
    }
}
int query(int l, int r, int id, int p) {
    if(l == r)
        return dep[id];
    else {
        push(id);
        int m = (l + r) >> 1;
        if(p <= m)
            return query(ls, p);
        return query(rs, p);
    }
}
std::set<int> cv;
typedef std::set<int>::iterator Iter;
int insert(int x, int siz) {
    Iter it = cv.insert(x).first;
    int dx;
    if(root) {
        if(it != cv.begin()) {
            Iter prev = it;
            int px = *--prev;
            if(!T[px].c[1])
                T[px].c[1] = x, T[x].p = px;
        }
        if(!T[x].p) {
            Iter nxt = it;
            int nx = *++nxt;
            T[nx].c[0] = x, T[x].p = nx;
        }
        dx = query(srt, T[x].p) + 1;
    } else {
        root = x, dx = 1;
    }
    reset(srt, x, dx);
    return dx;
}
void connect(int u, int p, int k) {
    T[u].p = p;
    T[p].c[k] = u;
}
int getMin(int siz) {
    int x = *cv.begin();
    if(x == root)
        return 1;
    int res = query(srt, x);
    int lp = x + 1, rp = T[x].p - 1;
    if(lp <= rp)
        modify(srt, lp, rp, -1);
    modify(srt, 1, siz, 1);
    reset(srt, x, 1);
    connect(T[x].c[1], T[x].p, 0);
    connect(root, x, 1);
    T[x].p = 0, root = x;
    return res;
}
int getMax(int siz) {
    int x = *cv.rbegin();
    if(x == root)
        return 1;
    int res = query(srt, x);
    int lp = T[x].p + 1, rp = x - 1;
    if(lp <= rp)
        modify(srt, lp, rp, -1);
    modify(srt, 1, siz, 1);
    reset(srt, x, 1);
    connect(T[x].c[0], T[x].p, 1);
    connect(root, x, 0);
    T[x].p = 0, root = x;
    return res;
}
int gdMin(int siz) {
    int res = getMin(siz);
    modify(srt, 1, siz, -1);
    cv.erase(root);
    root = T[root].c[1];
    T[root].p = 0;
    return res;
}
int gdMax(int siz) {
    int res = getMax(siz);
    modify(srt, 1, siz, -1);
    cv.erase(root);
    root = T[root].c[0];
    T[root].p = 0;
    return res;
}
int op[size], A[size];
int dispatch(int i, int siz) {
    switch(op[i]) {
        case 1:
            return insert(A[i], siz);
        case 2:
            return getMin(siz);
        case 3:
            return getMax(siz);
        case 4:
            return gdMin(siz);
        case 5:
            return gdMax(siz);
    }
    return 0;
}
struct Info {
    int id, val;
    Info() {}
    Info(int id, int val) : id(id), val(val) {}
    bool operator<(const Info& rhs) const {
        return val < rhs.val;
    }
} B[size];
int main() {
    int n = read(), siz = 0;
    for(int i = 0; i < n; ++i) {
        op[i] = read();
        if(op[i] == 1)
            B[++siz] = Info(i, read());
    }
    std::sort(B + 1, B + siz + 1);
    for(int i = 1; i <= siz; ++i)
        A[B[i].id] = i;
    for(int i = 0; i < n; ++i)
        printf("%d\n", dispatch(i, siz));
    return 0;
}
