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
const int size = 50005, mod = 201314;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
struct Edge {
    int to, nxt;
} E[size];
int last[size], cnt = 0;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int p[size], son[size];
int buildTree(int u) {
    int siz = 1, msiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        int vsiz = buildTree(v);
        if(msiz < vsiz)
            msiz = vsiz, son[u] = v;
        siz += vsiz;
    }
    return siz;
}
int top[size], id[size], icnt = 0;
void buildChain(int u) {
    id[u] = ++icnt;
    if(son[u]) {
        top[son[u]] = top[u];
        buildChain(son[u]);
    }
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!top[v]) {
            top[v] = v;
            buildChain(v);
        }
    }
}
int A[size][2], n;
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void addOne(int x) {
    int y = x;
    while(x <= n) {
        if(++A[x][0] == mod)
            A[x][0] = 0;
        A[x][1] = add(A[x][1], y);
        x += x & -x;
    }
}
void subOne(int x) {
    int y = x;
    while(x <= n) {
        if(--A[x][0] == -1)
            A[x][0] = mod - 1;
        A[x][1] = sub(A[x][1], y);
        x += x & -x;
    }
}
void modify(int nl, int nr) {
    addOne(nl);
    subOne(nr + 1);
}
int query(int x) {
    int y = x, resA = 0, resB = 0;
    while(x) {
        resA = add(resA, A[x][0]);
        resB = add(resB, A[x][1]);
        x -= x & -x;
    }
    int res =
        (static_cast<long long>(y + 1) * resA - resB) %
        mod;
    return res >= 0 ? res : res + mod;
}
int query(int nl, int nr) {
    return sub(query(nr), query(nl - 1));
}
void addChain(int u) {
    while(u) {
        modify(id[top[u]], id[u]);
        u = p[top[u]];
    }
}
int queryChain(int u) {
    int res = 0;
    while(u) {
        res = add(res, query(id[top[u]], id[u]));
        u = p[top[u]];
    }
    return res;
}
struct Query {
    int pos, z, id;
    bool op;
    bool operator<(const Query& rhs) const {
        return pos < rhs.pos;
    }
} Q[size * 2];
int res[size];
int main() {
    n = read();
    int q = read();
    for(int i = 2; i <= n; ++i) {
        p[i] = read() + 1;
        addEdge(p[i], i);
    }
    buildTree(1);
    top[1] = 1;
    buildChain(1);
    int qid = 0;
    for(int i = 1; i <= q; ++i) {
        int l = read() + 1;
        int r = read() + 1;
        int z = read() + 1;
        if(l != 1) {
            int id = qid++;
            Q[id].pos = l - 1;
            Q[id].z = z;
            Q[id].id = i;
        }
        int id = qid++;
        Q[id].pos = r;
        Q[id].z = z;
        Q[id].id = i;
        Q[id].op = true;
    }
    std::sort(Q, Q + qid);
    int cp = 0;
    for(int i = 0; i < qid; ++i) {
        while(cp < Q[i].pos)
            addChain(++cp);
        int val = queryChain(Q[i].z),
            &ans = res[Q[i].id];
        if(Q[i].op)
            ans = add(ans, val);
        else
            ans = (val ? mod - val : 0);
    }
    for(int i = 1; i <= q; ++i)
        printf("%d\n", res[i]);
    return 0;
}
