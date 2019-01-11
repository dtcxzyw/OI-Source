#include <cstdio>
const int size = 200005, maxS = 2 * size;
struct SAM {
    struct Node {
        int link, len, nxt[26], right;
    } T[maxS];
    int last, siz;
    SAM() : last(1), siz(1) {}
    void extend(int ch) {
        int p = last, id = ++siz;
        T[id].len = T[p].len + 1;
        T[id].right = 1;
        while(p && !T[p].nxt[ch]) {
            T[p].nxt[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].nxt[ch];
            if(T[p].len + 1 == T[q].len)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                T[cq].right = 0;
                while(p && T[p].nxt[ch] == q) {
                    T[p].nxt[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
    }
    int cnt[size], q[maxS];
    void init() {
        int c;
        do
            c = getchar();
        while(c < 'a' || c > 'z');
        while('a' <= c && c <= 'z') {
            extend(c - 'a');
            c = getchar();
        }
        int n = T[last].len;
        for(int i = 1; i <= siz; ++i)
            ++cnt[T[i].len];
        for(int i = 1; i <= n; ++i)
            cnt[i] += cnt[i - 1];
        for(int i = 1; i <= siz; ++i)
            q[cnt[T[i].len]--] = i;
        for(int i = siz; i >= 1; --i) {
            int u = q[i], p = T[u].link;
            T[p].right += T[u].right;
        }
    }
} A, B;
typedef long long Int64;
#define asInt64 static_cast<Int64>
Int64 sum = 0;
void DFS(int a, int b) {
    for(int i = 0; i < 26; ++i) {
        int u = A.T[a].nxt[i], v = B.T[b].nxt[i];
        if(u && v) {
            sum +=
                asInt64(A.T[u].right) * B.T[v].right;
            DFS(u, v);
        }
    }
}
int main() {
    A.init();
    B.init();
    DFS(1, 1);
    printf("%lld\n", sum);
    return 0;
}
