#include <cstdio>
#include <cstring>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size = 1005;
int buf[size], ans[size];
Int64 gcd(Int64 a, Int64 b) {
    return b ? gcd(b, a % b) : a;
}
int fd;
bool DFS(int d, Int64 a, Int64 b, int p) {
    if(b > a * 10000000)
        return false;
    if(d == fd) {
        if(b % a)
            return false;
        buf[d] = b / a;
        if(ans[d] > buf[d])
            memcpy(ans + 1, buf + 1, sizeof(int) * d);
        return true;
    }
    int np = b / a + 1;
    Int64 key = b * (fd - d + 1);
    if(p > np)
        np = p;
    bool flag = false;
    while(np * a < key) {
        buf[d] = np;
        Int64 na = a * np - b, nb = b * np,
              g = gcd(na, nb);
        flag |= DFS(d + 1, na / g, nb / g, np + 1);
        ++np;
    }
    return flag;
}
int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    fd = 0;
    do
        ans[++fd] = 10000005;
    while(!DFS(1, a, b, 2));
    for(int i = 1; i <= fd; ++i)
        printf("%d ", ans[i]);
    return 0;
}
