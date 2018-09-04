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
struct Node {
    int cnt, fa, rank;
    long long sum;
} T[size * 2];
int find(int u) {
    return T[u].fa == u ? u : find(T[u].fa);
}
void setP(int u, int p) {
    T[u].fa = p;
    T[p].sum += T[u].sum;
    T[p].cnt += T[u].cnt;
}
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u != v) {
        if(T[u].rank > T[v].rank) {
            setP(v, u);
        } else {
            setP(u, v);
            if(T[u].rank == T[v].rank)
                ++T[v].rank;
        }
    }
}
int id[size], cnt;
void move(int u, int v) {
    int fu = find(id[u]), fv = find(id[v]);
    if(fu != fv) {
        --T[fu].cnt;
        T[fu].sum -= u;
        id[u] = ++cnt;
        T[cnt].fa = fv;
        ++T[fv].cnt;
        T[fv].sum += u;
    }
}
int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        cnt = n;
        for(int i = 1; i <= n; ++i) {
            T[i].cnt = 1;
            T[i].fa = i;
            T[i].rank = 0;
            T[i].sum = i;
            id[i] = i;
        }
        while(m--) {
            int op = read();
            if(op == 3) {
                int p = find(id[read()]);
                printf("%d %lld\n", T[p].cnt,
                       T[p].sum);
            } else {
                int u = read();
                int v = read();
                if(op == 1)
                    merge(id[u], id[v]);
                else
                    move(u, v);
            }
        }
    }
    return 0;
}
