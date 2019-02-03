#include <algorithm>
#include <cstdio>
const int mod = 100000000, half = mod / 2;
struct BigNum {
    int num[150], siz;
    BigNum(int x = 0) : siz(1) {
        for(int i = 0; i < 150; ++i)
            num[i] = 0;
        num[1] = x;
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
    int count() const {
        int res = (siz - 1) * 8;
        int v = num[siz];
        while(v) {
            ++res;
            v /= 10;
        }
        return res;
    }
} res[10000];
int main() {
    res[1] = BigNum(1);
    res[2] = BigNum(1);
    for(int i = 3;; ++i) {
        res[i] = res[i - 1];
        res[i] += res[i - 2];
        if(res[i].count() >= 1000) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
