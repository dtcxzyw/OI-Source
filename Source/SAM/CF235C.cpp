#include <cstdio>
#include <cstring>
#include <set>
typedef std::set<int>::iterator IterT;
const int size = 1000005, maxS = 4 * size;
namespace SAM {
    struct Node {
        int nxt[26], link, len;
        std::set<int> rid;
    } T[maxS];
    int last, siz = 1;
    void extend(int sid, int ch) {
        putchar(ch + 'a');
        int id = ++siz;
        T[id].len = T[last].len + 1;
        if(sid)
            T[id].rid.insert(sid);
        int p = last;
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
                memcpy(T[cq].nxt, T[q].nxt,
                       sizeof(T[cq].nxt));
                T[cq].link = T[q].link;
                T[cq].len = T[p].len + 1;
                T[q].link = T[id].link = cq;
                while(p && T[p].nxt[ch] == q) {
                    T[p].nxt[ch] = cq;
                    p = T[p].link;
                }
            }
        } else
            T[id].link = 1;
        last = id;
    }
};
char buf[size], P[size];
int ans[size];
int main() {
    int n;
    scanf("%s%d", P, &n);
    for(int t = 1; t <= n; ++t) {
        scanf("%s", buf + 1);
        int len = strlen(buf + 1);
        SAM::last = 1;
        for(int i = 1; i < len; ++i)
            SAM::extend(0, buf[i] - 'a');
        SAM::extend(t, buf[len] - 'a');
        for(int i = 1; i < len; ++i)
            SAM::extend(t, buf[i] - 'a');
        puts("------------");
    }
    int cur = 1;
    for(int i = 0; P[i]; ++i) {
        int ch = P[i] - 'a';
        while(cur && !SAM::T[cur].nxt[ch])
            cur = SAM::T[cur].link;
        if(cur == 0)
            cur = 1;
        else {
            cur = SAM::T[cur].nxt[ch];
            int x = cur;
            while(x) {
                std::set<int>& id = SAM::T[x].rid;
                for(IterT it = id.begin();
                    it != id.end(); ++it)
                    ++ans[*it];
                x = SAM::T[x].link;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
