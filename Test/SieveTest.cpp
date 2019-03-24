#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
using Clock = std::chrono::high_resolution_clock;
const int N = 1000000;
void eratosthenes(int* p, bool* flag) {
    int pcnt = 0;
    for(int i = 2; i <= N; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            for(int j = i * 2; j <= N; j += i)
                flag[j] = true;
        }
    }
}
void euler(int* p, bool* flag) {
    int pcnt = 0;
    for(int i = 2; i <= N; ++i) {
        if(!flag[i])
            p[++pcnt] = i;
        for(int j = 1; j <= pcnt && i * p[j] <= N;
            ++j) {
            flag[i * p[j]] = true;
            if(i % p[j] == 0)
                break;
        }
    }
}
int p[2][N + 5];
bool flag[2][N + 5];
int main() {
    Clock::duration durA(0), durB(0);
    for(int i = 1; i <= 100; ++i) {
        memset(p, 0, sizeof(p));
        memset(flag, 0, sizeof(flag));

        auto begA = Clock::now();
        eratosthenes(p[0], flag[0]);
        durA += Clock::now() - begA;

        auto begB = Clock::now();
        euler(p[1], flag[1]);
        durB += Clock::now() - begB;

        if(memcmp(p[0], p[1], sizeof(p[0])) ||
           memcmp(flag[0], flag[1], sizeof(flag[0])))
            throw;
    }
    printf("%lf ms\n", durA.count() / 1e6);
    printf("%lf ms\n", durB.count() / 1e6);
    return 0;
}
