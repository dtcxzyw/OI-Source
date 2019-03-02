#include <algorithm>
#include <csetjmp>
#include <cstdio>
#include <cstring>
#include <vector>
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
int s;
int SG1(int x) {
    return x;
}
int SG2(int x) {
    if(s & 1)
        return x & 1;
    int val = x % (s + 1);
    if(val == s)
        return 2;
    return val % 2;
}
int SG3(int x) {
    return x / s;
}
int SG4(int x) {
    if(x == 0)
        return 0;
    switch(x & 3) {
        case 0:
            return x - 1;
        case 3:
            return x + 1;
        default:
            return x;
    }
}
typedef int (*SGFunc)(int);
SGFunc fun[5] = { 0, SG1, SG2, SG3, SG4 };
const int size = 30005;
struct Edge {
    int to, nxt;
} E[size * 2];
int last[size], cnt;
void addEdge(int u, int v) {
    ++cnt;
    E[cnt].to = v, E[cnt].nxt = last[u];
    last[u] = cnt;
}
int crt, tsiz, msiz, siz[size];
bool vis[size];
void reset() {
    memset(last, 0, sizeof(last));
    cnt = 0;
    memset(vis, 0, sizeof(vis));
}
void getRootImpl(int u, int p) {
    siz[u] = 1;
    int csiz = 0;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(p != v && !vis[v]) {
            getRootImpl(v, u);
            siz[u] += siz[v];
            csiz = std::max(csiz, siz[v]);
        }
    }
    csiz = std::max(csiz, tsiz - siz[u]);
    if(csiz < msiz)
        msiz = csiz, crt = u;
}
int getRoot(int u, int usiz) {
    tsiz = usiz, msiz = 1 << 30;
    getRootImpl(u, 0);
    return crt;
}
const int modv = 65537;
std::vector<int> LUT[modv];
bool findA(int val) {
    int id = val % modv;
    return std::find(LUT[id].begin(), LUT[id].end(),
                     val) != LUT[id].end();
}
int xcnt = 0, xbuf[size];
void insertA(int val) {
    if(!findA(val)) {
        LUT[val % modv].push_back(val);
        xbuf[++xcnt] = val % modv;
    }
}
void doClearA() {
    for(int i = 1; i <= xcnt; ++i)
        LUT[xbuf[i]].clear();
    xcnt = 0;
}
bool vcnt[4];
bool findB(int val) {
    return vcnt[val];
}
void insertB(int val) {
    vcnt[val] = true;
}
void doClearB() {
    memset(vcnt, 0, sizeof(vcnt));
}
typedef bool (*FindFunc)(int);
typedef void (*InsFunc)(int);
typedef void (*ClrFunc)();
FindFunc find;
InsFunc insert;
ClrFunc doClear;
jmp_buf buf[10], *cbuf;
int SG[size], ccnt, A[size];
void DFS(int u, int p, int xorv) {
    if(xorv == 0)
        longjmp(*cbuf, 1);
    A[++ccnt] = xorv;
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v != p && !vis[v])
            DFS(v, u, xorv ^ SG[v]);
    }
}
void solve(int u) {
    int rt = SG[u];
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            ccnt = 0;
            DFS(v, u, SG[v]);
            for(int i = 1; i <= ccnt; ++i) {
                int val = A[i] ^ rt;
                if(val == 0 || find(val))
                    longjmp(*cbuf, 1);
            }
            for(int i = 1; i <= ccnt; ++i)
                insert(A[i]);
        }
    }
    doClear();
}
void divide(int u) {
    vis[u] = true;
    solve(u);
    for(int i = last[u]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!vis[v]) {
            int nrt = getRoot(v, siz[v]);
            divide(nrt);
        }
    }
}
bool foo() {
    reset();
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    for(int i = 1; i <= n; ++i) {
        SG[i] = read();
        if(SG[i] == 0)
            return true;
    }
    int k = read();
    SGFunc sgf = fun[k];
    if(k == 2 || k == 3)
        s = read();
    for(int i = 1; i <= n; ++i)
        SG[i] = sgf(SG[i]);
    if(k == 2) {
        insert = insertB;
        find = findB;
        doClear = doClearB;
    } else {
        insert = insertA;
        find = findA;
        doClear = doClearA;
    }
    if(setjmp(*cbuf)) {
        doClear();
        return true;
    } else {
        divide(getRoot(1, n));
        return false;
    }
}
int main() {
    int t = read();
    for(int i = 1; i <= t; ++i) {
        cbuf = buf + i;
        puts(foo() ?
                 "Mutalisk ride face how to lose?" :
                 "The commentary cannot go on!");
    }
    return 0;
}
