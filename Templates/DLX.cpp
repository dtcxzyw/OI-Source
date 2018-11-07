#include <cstdio>
int getBit() {
    int c;
    do
        c = getchar();
    while(c < '0' || c > '1');
    return c;
}
const int maxa = 505, size = 5000 + maxa;
struct Node {
    int u, d, l, r, x, y;
} A[size];
int siz[maxa];
void mark(int c) {
    A[A[c].l].r = A[c].r, A[A[c].r].l = A[c].l;
    int c1 = A[c].d;
    while(c1 != c) {
        int c2 = A[c1].r;
        while(c2 != c1) {
            A[A[c2].u].d = A[c2].d;
            A[A[c2].d].u = A[c2].u;
            --siz[A[c2].x];
            c2 = A[c2].r;
        }
        c1 = A[c1].d;
    }
}
void unmark(int c) {
    int c1 = A[c].u;
    while(c1 != c) {
        int c2 = A[c1].l;
        while(c2 != c1) {
            A[A[c2].u].d = A[A[c2].d].u = c2;
            ++siz[A[c2].x];
            c2 = A[c2].l;
        }
        c1 = A[c1].u;
    }
    A[A[c].l].r = A[A[c].r].l = c;
}
int st[maxa], top = 0;
bool DLX() {
    if(!A[0].r) {
        for(int i = 1; i <= top; ++i)
            printf("%d ", st[i]);
        return true;
    }
    int cc = A[0].r, c, csiz = maxa;
    while(cc) {
        if(csiz > siz[cc])
            c = cc, csiz = siz[cc];
        cc = A[cc].r;
    }
    mark(c);
    int c1 = A[c].d;
    while(c1 != c) {
        int c2 = A[c1].r;
        while(c2 != c1) {
            mark(A[c2].x);
            c2 = A[c2].r;
        }
        st[++top] = A[c1].y;
        if(DLX())
            return true;
        --top;
        c2 = A[c1].l;
        while(c2 != c1) {
            unmark(A[c2].x);
            c2 = A[c2].l;
        }
        c1 = A[c1].d;
    }
    unmark(c);
    return false;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int cnt = m;
    A[0].l = m, A[m].r = 0;
    for(int i = 1; i <= m; ++i) {
        A[i - 1].r = i;
        A[i].l = i - 1;
        A[i].u = A[i].d = i;
    }
    for(int i = 1; i <= n; ++i) {
        int f = 0, l = 0;
        for(int j = 1; j <= m; ++j)
            if(getBit() == '1') {
                ++cnt;
                A[cnt].x = j;
                A[cnt].y = i;

                A[cnt].u = A[j].u;
                A[cnt].d = j;
                A[A[j].u].d = cnt;
                A[j].u = cnt;
                ++siz[j];

                if(f == 0)
                    f = cnt;
                if(l) {
                    A[cnt].l = l;
                    A[l].r = cnt;
                }
                l = cnt;
            }
        if(f)
            A[f].l = l, A[l].r = f;
    }
    if(!DLX())
        puts("No Solution!");
    return 0;
}
