#include <bitset>
#include <cstdio>
int main() {
    std::bitset<200> bit(
        "111011000010100000010001011000101100110100011"
        "011010010100001001101000001101100111010001110"
        "000100100101011100101010101001110010010");
    for(int i = 1000000; i <= 10000000; ++i) {
        long long res = 1, a = 19;
        for(int j = 0; j < 200; ++j) {
            if(bit[j])
                res = res * a % i;
            a = a * a % i;
        }
        if(res == 642666)
            printf("%d\n", i);
    }
    return 0;
}
