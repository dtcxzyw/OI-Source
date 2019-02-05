#include <cstdio>
#include <string>
std::string read() {
    std::string str;
    int c;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        str.push_back(c);
        c = getchar();
    }
    return str;
}
const int size = 360005;
struct Node {
    int ch[26], fail;
} T[size];
int icnt = 0;
int insert() {
    int c, p = 0;
    do
        c = getchar();
    while(c < 'a' || c > 'z');
    while('a' <= c && c <= 'z') {
        int& v = T[p].ch[c - 'a'];
        if(!v)
            v = ++icnt;
        p = v;
        c = getchar();
    }
    return p;
}
int q[size];
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
int cnt[size], last[size];
void match(int id, const std::string& str) {
    int p = 0;
    for(int i = 0; i < str.size(); ++i) {
        int ch = str[i] - 'a';
        p = T[p].ch[ch];
        int cp = p;
        while(cp) {
            if(last[cp] != id)
                last[cp] = id, ++cnt[cp];
            cp = T[cp].fail;
        }
    }
}
int endPos[60005];
std::string P[10005];
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i)
        P[i] = read();
    for(int i = 1; i <= q; ++i)
        endPos[i] = insert();
    cook();
    for(int i = 1; i <= n; ++i)
        match(i, P[i]);
    for(int i = 1; i <= q; ++i)
        printf("%d\n", cnt[endPos[i]]);
    return 0;
}
