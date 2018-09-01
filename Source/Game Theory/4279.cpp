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
bool foo() {
    int n = read(), sg = 0;
    bool flag = true;
    while(n--) {
        int x = read();
        sg ^= x;
        flag &= x == 1;
    }
    return static_cast<bool>(sg) ^ flag;
}
int main() {
    int t = read();
    while(t--)
        puts(foo() ? "John" : "Brother");
    return 0;
}
