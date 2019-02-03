#include <cstdio>
class BigNum {
private:
    static const int bit = 9;
    static const unsigned long long mod =
        1000000000ULL;
    unsigned int mData[2021];
    int mSize;

public:
    BigNum(int i) : mSize(1) {
        mData[0] = i;
    }
    void operator*=(long long rhs) {
        if(rhs == 0)
            mSize = 1, mData[0] = 0;
        if(mSize == 1 && mData[0] == 0)
            return;
        unsigned long long tmp = 0;
        for(int i = 0; i < mSize; ++i) {
            tmp += mData[i] * rhs;
            mData[i] = tmp % mod;
            tmp /= mod;
        }
        if(tmp) {
            mData[mSize] = tmp;
            ++mSize;
        }
    }
    int count() const {
        int res = 0;
        for(int i = 0; i < mSize; ++i) {
            int x = mData[i];
            while(x) {
                res += x % 10;
                x /= 10;
            }
        }
        return res;
    }
};
int main() {
    BigNum res(1);
    for(int i = 1; i <= 100; ++i)
        res *= i;
    printf("%d\n", res.count());
    return 0;
}
