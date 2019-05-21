#include <chrono>
#include <cstdio>
#include <fstream>
#include <random>
const int size = 10000005;
bool flag[size];
int p[size], pcnt = 0;
void pre(int n) {
    for(int i = 2; i <= n; ++i) {
        if(!flag[i])
            p[++pcnt] = i;
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            flag[i * p[j]] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
std::random_device rd;
using Int64 = long long;
#define asInt64 static_cast<Int64>
Int64 powm(Int64 a, int k, int mod) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
const int regCnt = 5000;
int reg[regCnt + 5];
void check(int pos) {
    if(pos < 1 || pos > regCnt)
        throw;
}
int sim(int x, int y, int d, int mod) {
    reg[1] = x, reg[2] = y;
    for(int i = 3; i <= regCnt; ++i)
        reg[i] = 1;
    std::ifstream in("output");
    for(int i = 1; i <= regCnt; ++i) {
        char op[5];
        in >> op;
        switch(*op) {
            case '+': {
                int a, b, c;
                in >> a >> b >> c;
                check(a);
                check(b);
                check(c);
                reg[c] = (reg[a] + reg[b]) % mod;
            } break;
            case '^': {
                int a, b;
                in >> a >> b;
                reg[b] = powm(reg[a], d, mod);
            } break;
            case 'f': {
                int pos;
                in >> pos;
                check(pos);
                return reg[pos];
            } break;
        }
    }
    return -1;
}
void foo() {
    std::uniform_int_distribution<int> uid(2, pcnt);
    int mod = p[uid(rd)];
    std::uniform_int_distribution<int> did(
        2, std::min(10, mod - 1));
    int d = did(rd);
    {
        std::ofstream out("input");
        out << d << " " << mod;
    }
    int res = system("./CF1060H.out <input >output");
    if(res != 0) {
        puts("boom");
        throw;
    }
    for(int i = 1; i <= 1000; ++i) {
        std::uniform_int_distribution<int> gen(0, mod -
                                                   1);
        int x = gen(rd), y = gen(rd);
        if(sim(x, y, d, mod) != asInt64(x) * y % mod) {
            puts("failed");
            throw;
        }
    }
}
int main() {
    pre(10000000);
    for(int i = 1; i <= 500; ++i) {
        printf("pass %d\n", i);
        foo();
    }
    return 0;
}
