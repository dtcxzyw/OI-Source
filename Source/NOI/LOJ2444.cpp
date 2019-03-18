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
struct G {
    struct Edge {
        int to, nxt;
    } E[size];
    int last[size], cnt;
    G() : cnt(0) {}
    void addEdge(int u, int v) {
        ++cnt;
        E[cnt].to = v, E[cnt].nxt = last[u];
        last[u] = cnt;
    }
} F, Q;
struct Node {
    int ch[26], p, fail;
} T[size];
int tcnt = 0, q[size];
void cook() {
    int b = 0, e = 0;
    for(int i = 0; i < 26; ++i)
        if(T[0].ch[i])
            q[e++] = T[0].ch[i];
    while(b != e) {
        int u = q[b++];
        for(int i = 0; i < 26; ++i) {
            int& v = T[u].ch[i];
            if(v) {
                T[v].fail = T[T[u].fail].ch[i];
                q[e++] = v;
            } else
                v = T[T[u].fail].ch[i];
        }
    }
}
int L[size], R[size], icnt = 0;
void DFS(int u) {
    L[u] = ++icnt;
    for(int i = F.last[u]; i; i = F.E[i].nxt) {
        int v = F.E[i].to;
        DFS(v);
    }
    R[u] = icnt;
}
int A[size];
void modify(int x, int op) {
    while(x <= icnt) {
        A[x] += op;
        x += x & -x;
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += A[x];
        x -= x & -x;
    }
    return res;
}
char P[size];
int cnt[size], pos[size];
int main() {
    scanf("%s", P);
    int n = read();
    for(int i = 1; i <= n; ++i) {
        int u = read();
        int v = read();
        Q.addEdge(v, u);
    }
    int pcnt = 0;
    for(int i = 0, cp = 0; P[i]; ++i)
        switch(P[i]) {
            case 'B':
                cp = T[cp].p;
                break;
            case 'P':
                pos[++pcnt] = cp;
                break;
            default: {
                int& nxt = T[cp].ch[P[i] - 'a'];
                if(!nxt) {
                    nxt = ++tcnt;
                    T[nxt].p = cp;
                }
                cp = nxt;
            } break;
        }
    cook();
    for(int i = 1; i <= tcnt; ++i)
        F.addEdge(T[i].fail, i);
    DFS(0);
    pcnt = 0;
    for(int i = 0, cp = 0; P[i]; ++i)
        switch(P[i]) {
            case 'B': {
                modify(L[cp], -1);
                cp = T[cp].p;
            } break;
            case 'P': {
                ++pcnt;
                for(int e = Q.last[pcnt]; e;
                    e = Q.E[e].nxt) {
                    int x = pos[Q.E[e].to];
                    cnt[e] =
                        query(R[x]) - query(L[x] - 1);
                }
            } break;
            default: {
                cp = T[cp].ch[P[i] - 'a'];
                modify(L[cp], 1);
            } break;
        }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", cnt[i]);
    return 0;
}
