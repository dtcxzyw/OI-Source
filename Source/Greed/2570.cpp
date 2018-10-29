#include <algorithm>
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
typedef double FT;
const FT eps = 1e-8;
const int size = 35;
struct Info {
    FT p;
    int b, e;
} A[size], Q[size];
bool cmpBeg(const Info& a, const Info& b) {
    return a.b < b.b;
}
bool cmpEnd(const Info& a, const Info& b) {
    return a.e < b.e;
}
struct Mouse {
    int id, s;
    bool operator<(const Mouse& rhs) const {
        return s > rhs.s;
    }
} M[size];
bool check(int n, int m, FT T) {
    int b = 0, e = 0, cp = 0;
    for(int i = 0; i < m; ++i)
        M[i].id = -1;
    FT ct = 0.0;
    while(cp < n || b < e) {
        FT pt = A[cp].b;
        FT et = 1e20;
        for(int i = 0; i < m && M[i].id != -1; ++i)
            et = std::min(et, Q[M[i].id].p / M[i].s);
        if(pt < et + ct) {
            Q[e++] = A[cp++];
            et = pt - ct;
            ct = pt;
        } else
            ct += et;
        for(int i = 0; i < m && M[i].id != -1; ++i) {
            Info& q = Q[M[i].id];
            q.p -= M[i].s * et;
            if(q.p < eps) {
                if(ct > q.e + T)
                    return false;
                q.e = -1;
            }
        }
        std::sort(Q + b, Q + e, cmpEnd);
        while(b < e && Q[b].e == -1)
            ++b;
        for(int i = 0; i < m; ++i)
            M[i].id = -1;
        for(int i = b, j = 0; i < e && j < m; ++i, ++j)
            M[j].id = i;
    }
    return true;
}
FT foo() {
    int n = read();
    int m = read();
    for(int i = 0; i < n; ++i) {
        A[i].p = read();
        A[i].b = read();
        A[i].e = read();
    }
    std::sort(A, A + n, cmpBeg);
    A[n].b = 1 << 30;
    for(int i = 0; i < m; ++i)
        M[i].s = read();
    std::sort(M, M + m);
    FT l = 0.0, r = 1e10, ans;
    while(r - l >= 1e-6) {
        FT mid = (l + r) * 0.5;
        if(check(n, m, mid))
            r = ans = mid;
        else
            l = mid;
    }
    return ans;
}
int main() {
    int t = read();
    while(t--)
        printf("%.6lf\n", foo());
    return 0;
}
