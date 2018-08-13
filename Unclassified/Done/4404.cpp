#include <algorithm>
#include <cstdio>
#include <cstring>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while (c < '0' || c > '9');
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
struct Key {
    int id, nxt;
    Key() {}
    Key(int id, int nxt) : id(id), nxt(nxt) {}
    bool operator<(const Key &rhs) const {
        return nxt < rhs.nxt;
    }
};
const int size = 100005;
int maxi[size << 2], val[size];
int choose(int u, int v) {
    return val[u] > val[v] ? u : v;
}
void modify(int l, int r, int id, int p) {
    if (l != r) {
        int m = (l + r) >> 1;
        if (p <= m)
            modify(l, m, id << 1, p);
        else
            modify(m + 1, r, id << 1 | 1, p);
        maxi[id] = choose(maxi[id << 1], maxi[id << 1 | 1]);
    } else
        maxi[id] = l;
}
int A[size], B[size], nxt[size], head[size] = {};
bool flag[size] = {};
int main() {
    int n = read();
    int m = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read();
    memcpy(B + 1, A + 1, sizeof(int) * n);
    std::sort(B + 1, B + n + 1);
    int siz = std::unique(B + 1, B + n + 1) - (B + 1);
    for (int i = 1; i <= n; ++i) {
        int id = std::lower_bound(B + 1, B + siz + 1, A[i]) - B;
        A[i] = id;
        nxt[head[id]] = i;
        head[id] = i;
    }
    for (int i = 1; i <= siz; ++i)
        nxt[head[i]] = 1 << 30;
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int id = A[i];
        if (!flag[id]) {
            if (cnt == m) {
                int del = maxi[1];
                flag[del] = false;
                val[del] = 0;
                modify(1, siz, 1, del);
            } else
                ++cnt;
            flag[id] = true;
            ++ans;
        }
        val[id] = nxt[i];
        modify(1, siz, 1, id);
    }
    printf("%d\n", ans);
    return 0;
}
