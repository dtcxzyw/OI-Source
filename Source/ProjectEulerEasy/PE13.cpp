#include <algorithm>
#include <cstdio>
#include <cstring>
const int mod = 100000000, half = mod / 2;
char buf[256];
void readi(int& a, int l, int r) {
    a = 0;
    for(int i = l; i < r; ++i)
        a = a * 10 + buf[i] - '0';
}
struct BigNum {
    int num[15], siz;
    BigNum(int x = 0) : siz(1) {
        for(int i = 0; i < 15; ++i)
            num[i] = 0;
        num[1] = x;
    }
    void read() {
        scanf("%s", buf);
        int l = strlen(buf), r;
        siz = 1;
        while(true) {
            r = l, l = r - 8;
            readi(num[siz], std::max(l, 0), r);
            if(l > 0)
                siz++;
            else
                break;
        }
    }
    void update() {
        for(int i = 1; i <= siz; ++i)
            if(num[i] >= mod) {
                num[i] -= mod;
                ++num[i + 1];
            }
        if(num[siz + 1])
            ++siz;
    }
    void operator+=(const BigNum& rhs) {
        siz = std::max(siz, rhs.siz);
        for(int i = 1; i <= siz; ++i)
            num[i] += rhs.num[i];
        update();
    }
    void print() const {
        printf("%d", num[siz]);
        for(int i = siz - 1; i >= 1; --i)
            printf("%08d", num[i]);
        puts("");
    }
};
int main() {
    BigNum res;
    for(int i = 0; i < 100; ++i) {
        BigNum a;
        a.read();
        res += a;
    }
    res.print();
    return 0;
}
