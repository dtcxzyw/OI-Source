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
const int size = 100100;
struct Key {
    int key, id;
    bool operator<(Key rhs) const {
        return key != rhs.key ? key > rhs.key :
                                id > rhs.id;
    }
};
struct Node {
    Key key;
    int son, bro;
} T[size];
void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}
int merge(int u, int v) {
    if(u && v) {
        if(T[u].key < T[v].key)
            swap(u, v);
        T[v].bro = T[u].son;
        T[u].son = v;
        return u;
    }
    return u | v;
}
int mergeBro(int u) {
    if(u && T[u].bro) {
        int a = T[u].bro, b = T[a].bro;
        T[u].bro = T[a].bro = 0;
        return merge(merge(u, a), mergeBro(b));
    }
    return u;
}
int fa[size], root[size];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
bool flag[size];
int main() {
    int n = read();
    int m = read();
    for(int i = 1; i <= n; ++i) {
        T[i].key.key = read();
        T[i].key.id = i;
    }
    for(int i = 1; i <= n; ++i)
        root[i] = fa[i] = i;
    for(int i = 0; i < m; ++i)
        if(read() == 1) {
            int u = read(), v = read();
            if(flag[u] || flag[v])
                continue;
            int fu = find(u);
            int fv = find(v);
            if(fu != fv)
                fa[fv] = fu,
                root[fu] = merge(root[fu], root[fv]);
        } else {
            int u = read();
            if(flag[u])
                puts("-1");
            else {
                int fu = find(u);
                int rt = root[fu];
                Key val = T[rt].key;
                root[fu] = mergeBro(T[rt].son);
                printf("%d\n", val.key);
                flag[val.id] = true;
            }
        }
    return 0;
}
