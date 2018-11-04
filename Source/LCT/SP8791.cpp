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
int getOp() {
    int c, res;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        res = c;
        c = getchar();
    }
    return res;
}
const int size = 100005;
struct Node {
    int p, c[2];
} T[size];
#define ls T[u].c[0]
#define rs T[u].c[1]
int getPos(int u) {
    int p = T[u].p;
    return u == T[p].c[1];
}
bool isRoot(int u) {
    int p = T[u].p;
    return T[p].c[0] != u && T[p].c[1] != u;
}
void connect(int u, int p, int c) {
    T[p].c[c] = u;
    T[u].p = p;
}
void rotate(int u) {
    int ku = getPos(u);
    int p = T[u].p;
    int kp = getPos(p);
    int pp = T[p].p;
    int t = T[u].c[ku ^ 1];
    if(isRoot(p))
        T[u].p = pp;
    else
        connect(u, pp, kp);
    connect(p, u, ku ^ 1);
    connect(t, p, ku);
}
void splay(int u) {
    while(!isRoot(u)) {
        int p = T[u].p;
        if(!isRoot(p))
            rotate(getPos(p) == getPos(u) ? p : u);
        rotate(u);
    }
}
int access(int u) {
    int v = 0;
    do {
        splay(u);
        rs = v;
        v = u;
        u = T[u].p;
    } while(u);
    return v;
}
int main() {
    int n = read();
    int m = read();
    while(m--)
        switch(getOp()) {
            case 'k': {
                int u = read();
                int v = read();
                access(u);
                splay(u);
                T[u].p = v;
            } break;
            case 't': {
                int u = read();
                access(u);
                splay(u);
                T[ls].p = 0;
                ls = 0;
            } break;
            case 'a': {
                access(read());
                printf("%d\n", access(read()));
            } break;
        }
    return 0;
}
