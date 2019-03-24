#include <algorithm>
#include <cstdio>
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
struct Range {
    int minv, maxv;
    Range() {}
    Range(int minv, int maxv)
        : minv(minv), maxv(maxv) {}
    Range operator+(const Range& rhs) const {
        return Range(std::min(minv, rhs.minv),
                     std::max(maxv, rhs.maxv));
    }
};
struct Node {
    Range A, B;
    bool rev;
} T[size << 2];
void update(int id) {
    T[id].A = T[id << 1].A + T[id << 1 | 1].A;
    T[id].B = T[id << 1].B + T[id << 1 | 1].B;
}
void colorRev(int id) {
    std::swap(T[id].A, T[id].B);
    T[id].rev ^= 1;
}
void push(int id) {
    if(T[id].rev) {
        colorRev(id << 1);
        colorRev(id << 1 | 1);
        T[id].rev = false;
    }
}
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void reverse(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        colorRev(id);
    else {
        push(id);
        int m = (l + r) >> 1;
        if(nl <= m)
            reverse(ls, nl, nr);
        if(m < nr)
            reverse(rs, nl, nr);
        update(id);
    }
}
const int inf = 1 << 30;
bool dir[size];
void modify(int l, int r, int id, int p, int val) {
    if(l == r) {
        T[id].A = Range(val, -inf);
        T[id].B = Range(inf, val);
        if(T[id].rev ^ dir[l])
            std::swap(T[id].A, T[id].B);
    } else {
        push(id);
        int m = (l + r) >> 1;
        if(p <= m)
            modify(ls, p, val);
        else
            modify(rs, p, val);
        update(id);
    }
}
bool flag;
int K;
void query(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        flag &= K < T[id].A.minv && K > T[id].A.maxv;
    else {
        push(id);
        int m = (l + r) >> 1;
        if(nl <= m)
            query(ls, nl, nr);
        if(flag && m < nr)
            query(rs, nl, nr);
    }
}
int ch[size][2], siz[size], son[size], p[size];
void buildTree(int u) {
    siz[u] = 1;
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(!v)
            continue;
        p[v] = u;
        buildTree(v);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
            son[u] = v;
    }
}
int top[size], id[size], A[size], AP[size], icnt = 0;
bool tdir[size];
void buildChain(int u) {
    id[u] = ++icnt;
    dir[icnt] = tdir[u];
    AP[icnt] = A[p[u]];
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = 0; i < 2; ++i) {
        int v = ch[u][i];
        if(top[v])
            continue;
        top[v] = v;
        buildChain(v);
    }
}
void build(int l, int r, int id) {
    if(l == r) {
        if(AP[l]) {
            int val = AP[l];
            T[id].A = Range(val, -inf);
            T[id].B = Range(inf, val);
            if(dir[l])
                std::swap(T[id].A, T[id].B);
        } else
            T[id].A = T[id].B = Range(inf, -inf);
    } else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        update(id);
    }
}
bool nrt[size];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        A[i] = read();
        ch[i][0] = read();
        tdir[ch[i][0]] = 0;
        ch[i][1] = read();
        tdir[ch[i][1]] = 1;
        nrt[ch[i][0]] = nrt[ch[i][1]] = true;
    }
    int rt = 0;
    for(int i = 1; i <= n; ++i)
        if(!nrt[i]) {
            rt = i;
            break;
        }
    buildTree(rt);
    top[rt] = rt, top[0] = -1;
    buildChain(rt);
    build(1, n, 1);
    for(int i = 1; i <= m; ++i) {
        int op = read();
        int x = read();
        switch(op) {
            case 1: {
                int y = read();
                A[x] = y;
                if(ch[x][0])
                    modify(1, n, 1, id[ch[x][0]], y);
                if(ch[x][1])
                    modify(1, n, 1, id[ch[x][1]], y);
            } break;
            case 2: {
                if(siz[x] > 1)
                    reverse(1, n, 1, id[x] + 1,
                            id[x] + siz[x] - 1);
            } break;
            case 3: {
                K = A[x];
                flag = true;
                while(x && flag) {
                    query(1, n, 1, id[top[x]], id[x]);
                    x = p[top[x]];
                }
                puts(flag ? "YES" : "NO");
            } break;
        }
    }
    return 0;
}
