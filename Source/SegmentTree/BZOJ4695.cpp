#include <algorithm>
#include <cstdio>
int read() {
    int res = 0, c;
    bool flag = false;
    do {
        c = getchar();
        flag |= c == '-';
    } while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}
const int size = 500005, inf = 1 << 30;
typedef long long Int64;
#define asInt64 static_cast<Int64>
struct Node {
    Int64 sum;
    int maxv, cmax, smaxv;
    int minv, cmin, sminv;
    int lazy;
} T[size << 2];
#define ls l, m, id << 1
#define rs m + 1, r, id << 1 | 1
void update(int id) {
    int l = id << 1, r = id << 1 | 1;
    T[id].sum = T[l].sum + T[r].sum;

    if(T[l].maxv == T[r].maxv) {
        T[id].maxv = T[l].maxv;
        T[id].cmax = T[l].cmax + T[r].cmax;
        T[id].smaxv = std::max(T[l].smaxv, T[r].smaxv);
    } else {
        if(T[l].maxv < T[r].maxv)
            std::swap(l, r);
        T[id].maxv = T[l].maxv;
        T[id].cmax = T[l].cmax;
        T[id].smaxv = std::max(T[l].smaxv, T[r].maxv);
    }

    if(T[l].minv == T[r].minv) {
        T[id].minv = T[l].minv;
        T[id].cmin = T[l].cmin + T[r].cmin;
        T[id].sminv = std::min(T[l].sminv, T[r].sminv);
    } else {
        if(T[l].minv > T[r].minv)
            std::swap(l, r);
        T[id].minv = T[l].minv;
        T[id].cmin = T[l].cmin;
        T[id].sminv = std::min(T[l].sminv, T[r].minv);
    }
}
void build(int l, int r, int id) {
    if(l == r) {
        T[id].sum = T[id].minv = T[id].maxv = read();
        T[id].cmin = T[id].cmax = 1;
        T[id].sminv = inf, T[id].smaxv = -inf;
    } else {
        int m = (l + r) >> 1;
        build(ls);
        build(rs);
        update(id);
    }
}
void color(int l, int r, int id, int val) {
    T[id].sum += asInt64(r - l + 1) * val;
    T[id].maxv += val, T[id].smaxv += val;
    T[id].minv += val, T[id].sminv += val;
    T[id].lazy += val;
}
void reset(int l, int r, int id, int val) {
    T[id].sum = asInt64(r - l + 1) * val;
    T[id].smaxv = -inf, T[id].sminv = inf;
    T[id].cmax = T[id].cmin = r - l + 1;
}
void chkMax(int l, int r, int id, int val) {
    T[id].sum +=
        asInt64(val - T[id].maxv) * T[id].cmax;
    T[id].maxv = val;
    T[id].minv = std::min(T[id].minv, val);
    if(T[id].maxv == T[id].minv)
        reset(l, r, id, val);
    else
        T[id].sminv = std::min(T[id].sminv, val);
}
void chkMin(int l, int r, int id, int val) {
    T[id].sum +=
        asInt64(val - T[id].minv) * T[id].cmin;
    T[id].minv = val;
    T[id].maxv = std::max(T[id].maxv, val);
    if(T[id].maxv == T[id].minv)
        reset(l, r, id, val);
    else
        T[id].smaxv = std::max(T[id].smaxv, val);
}
void push(int l, int r, int id) {
    int m = (l + r) >> 1;
    if(T[id].lazy) {
        color(ls, T[id].lazy);
        color(rs, T[id].lazy);
        T[id].lazy = 0;
    }
    if(T[id].maxv < T[id << 1].maxv)
        chkMax(ls, T[id].maxv);
    if(T[id].maxv < T[id << 1 | 1].maxv)
        chkMax(rs, T[id].maxv);
    if(T[id].minv > T[id << 1].minv)
        chkMin(ls, T[id].minv);
    if(T[id].minv > T[id << 1 | 1].minv)
        chkMin(rs, T[id].minv);
}
void add(int l, int r, int id, int nl, int nr,
         int val) {
    if(nl <= l && r <= nr)
        color(l, r, id, val);
    else {
        push(l, r, id);
        int m = (l + r) >> 1;
        if(nl <= m)
            add(ls, nl, nr, val);
        if(m < nr)
            add(rs, nl, nr, val);
        update(id);
    }
}
void CASMax(int l, int r, int id, int nl, int nr,
            int val) {
    if(T[id].maxv <= val)
        return;
    if(nl <= l && r <= nr && val > T[id].smaxv)
        chkMax(l, r, id, val);
    else {
        push(l, r, id);
        int m = (l + r) >> 1;
        if(nl <= m)
            CASMax(ls, nl, nr, val);
        if(m < nr)
            CASMax(rs, nl, nr, val);
        update(id);
    }
}
void CASMin(int l, int r, int id, int nl, int nr,
            int val) {
    if(T[id].minv >= val)
        return;
    if(nl <= l && r <= nr && val < T[id].sminv)
        chkMin(l, r, id, val);
    else {
        push(l, r, id);
        int m = (l + r) >> 1;
        if(nl <= m)
            CASMin(ls, nl, nr, val);
        if(m < nr)
            CASMin(rs, nl, nr, val);
        update(id);
    }
}
Int64 querySum(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return T[id].sum;
    push(l, r, id);
    int m = (l + r) >> 1;
    Int64 res = 0;
    if(nl <= m)
        res += querySum(ls, nl, nr);
    if(m < nr)
        res += querySum(rs, nl, nr);
    return res;
}
int queryMin(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return T[id].minv;
    push(l, r, id);
    int m = (l + r) >> 1;
    if(nl <= m && m < nr)
        return std::min(queryMin(ls, nl, nr),
                        queryMin(rs, nl, nr));
    if(nl <= m)
        return queryMin(ls, nl, nr);
    return queryMin(rs, nl, nr);
}
int queryMax(int l, int r, int id, int nl, int nr) {
    if(nl <= l && r <= nr)
        return T[id].maxv;
    push(l, r, id);
    int m = (l + r) >> 1;
    if(nl <= m && m < nr)
        return std::max(queryMax(ls, nl, nr),
                        queryMax(rs, nl, nr));
    if(nl <= m)
        return queryMax(ls, nl, nr);
    return queryMax(rs, nl, nr);
}
#define root 1, n, 1
int main() {
    int n = read();
    build(1, n, 1);
    int m = read();
    for(int i = 1; i <= m; ++i) {
        int op = read();
        int l = read();
        int r = read();
        switch(op) {
            case 1:
                add(root, l, r, read());
                break;
            case 2:
                CASMin(root, l, r, read());
                break;
            case 3:
                CASMax(root, l, r, read());
                break;
            case 4:
                printf("%lld\n", querySum(root, l, r));
                break;
            case 5:
                printf("%d\n", queryMax(root, l, r));
                break;
            case 6:
                printf("%d\n", queryMin(root, l, r));
                break;
        }
    }
    return 0;
}
