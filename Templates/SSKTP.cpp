// TODO:2483
#include <algorithm>
#include <cctype>
#include <cstdio>
typedef double FT;
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
FT readFT() {
    int c;
    do
        c = getchar();
    while(!isprint(c));
    char str[32];
    int pos = 0;
    while(isprint(c)) {
        str[pos++] = c;
        c = getchar();
    }
    return strtod(str, 0);
}
const int size = 5005;
struct Node {
    int val, ls, rs, dis;
} T[size];
int merge(int u, int v) {
    if(u && v) {
        if(u < v)
            std::swap(u, v);
        T[u].rs = merge(T[u].rs, v);
        if(T[T[u].ls].dis < T[T[u].rs].dis)
            std::swap(T[u].ls, T[u].rs);
        T[u].dis = T[T[u].rs].dis + 1;
        return u;
    }
    return u | v;
}
int main() {
    int n = read();
    int m = read();
    int e = readFT() + 1e-6;
    return 0;
}
