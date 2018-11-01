#include <cstdio>
const int size = 2000005, k = 131;
struct Edge {
    int c, nxt[26];
} T[size];
void insert(const char* str, int siz) {
    static int icnt = 0;
    int p = 0;
    for(int i = 0; i < siz; ++i) {
        int c = str[i] - 'a';
        int& t = T[p].nxt[c];
        if(!t)
            t = ++icnt;
        p = t;
    }
    ++T[p].c;
}
char buf[size];
typedef unsigned long long HashT;
HashT L[size], R[size], P[size];
int end[size];
HashT hashL(int l, int r) {
    return L[r] - L[l - 1] * P[r - l + 1];
}
HashT hashR(int l, int r) {
    return R[l] - R[r + 1] * P[r - l + 1];
}
bool check(int l, int r) {
    if(l >= r)
        return true;
    int siz = (r - l + 1) >> 1;
    return hashL(l, l + siz - 1) ==
        hashR(r - siz + 1, r);
}
int main() {
    int n;
    scanf("%d", &n);
    int cp = 1;
    for(int i = 1; i <= n; ++i) {
        int k;
        scanf("%d %s", &k, buf + cp);
        insert(buf + cp, k);
        cp += k;
        end[i] = cp;
    }
    for(int i = 1; i <= cp; ++i)
        L[i] = L[i - 1] * k + buf[i];
    for(int i = cp; i >= 1; --i)
        R[i] = R[i + 1] * k + buf[i];
    P[0] = 1;
    for(int i = 1; i <= cp; ++i)
        P[i] = P[i - 1] * k;
    long long ans = n;
    cp = 1;
    for(int i = 1; i <= n; ++i) {
        int ep = end[i], p = 0;
        while(cp < ep) {
            p = T[p].nxt[buf[cp] - 'a'];
            if(p == 0)
                break;
            if(T[p].c && check(cp + 1, ep - 1))
                ans += (cp == ep - 1 ? T[p].c - 1 :
                                       2 * T[p].c);
            ++cp;
        }
        cp = ep;
    }
    printf("%lld\n", ans);
    return 0;
}
