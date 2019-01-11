#include <cstdio>
#include <map>
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
struct SAM {
    struct Node {
        int link, len;
        std::map<int, int> nxt;
    } T[size * 2];
    int last, siz;
    SAM() : last(1), siz(1) {}
    int extend(int ch) {
        int p = last, id = ++siz;
        T[id].len = T[last].len + 1;
        while(p && !T[p].nxt.count(ch)) {
            T[p].nxt[ch] = id;
            p = T[p].link;
        }
        if(p) {
            int q = T[p].nxt[ch];
            if(T[q].len == T[p].len + 1)
                T[id].link = q;
            else {
                int cq = ++siz;
                T[cq] = T[q];
                T[cq].len = T[p].len + 1;
                while(p && T[p].nxt[ch] == q) {
                    T[p].nxt[ch] = cq;
                    p = T[p].link;
                }
                T[q].link = T[id].link = cq;
            }
        } else
            T[id].link = 1;
        last = id;
        return T[id].len - T[T[id].link].len;
    }
} sam;
int main() {
    int n = read();
    long long cnt = 0;
    while(n--)
        printf("%lld\n", cnt += sam.extend(read()));
    return 0;
}
