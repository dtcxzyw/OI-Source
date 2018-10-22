#include <chrono>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
const int N = 1000, mod = 1000000007;
using Clock = std::chrono::high_resolution_clock;
class Timer {
private:
    const char* func;
    Clock::time_point beg;

public:
    Timer(const char* func)
        : func(func), beg(Clock::now()) {}
    ~Timer() {
        printf("%s %.3lf ms ", func,
               (Clock::now() - beg).count() * 1e-6);
    }
};
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
int A[N][N], B[N][N], C[N][N], D[N][N];
void mulStandard() {
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            for(int k = 0; k < N; ++k)
                C[i][j] =
                    (C[i][j] +
                     asInt64(A[i][k]) * B[k][j]) %
                    mod;
}
const Int64 end = std::numeric_limits<Int64>::max() -
    asInt64(mod - 1) * (mod - 1);
void mulOptimizedMod() {
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j) {
            Int64 sum = 0;
            for(int k = 0; k < N; ++k) {
                sum += asInt64(A[i][k]) * B[k][j];
                if(sum >= end)
                    sum %= mod;
            }
            C[i][j] = sum % mod;
        }
}
Int64 E[N][N];
void mulOptimizedCache() {
    memset(E, 0, sizeof(E));
    for(int i = 0; i < N; ++i) {
        Int64 *eib = &E[i][0], *eie = &E[i][N];
        for(int k = 0; k < N; ++k) {
            Int64 aik = A[i][k];
            int* bkj = &B[k][0];
            for(Int64 *eij = eib; eij != eie;
                ++eij, ++bkj) {
                *eij += aik * (*bkj);
                if(*eij >= end)
                    *eij %= mod;
            }
        }
    }
    for(int i = 0; i < N; ++i) {
        Int64 *eib = &E[i][0], *eie = &E[i][N];
        int* cij = &C[i][0];
        for(Int64 *eij = eib; eij != eie; ++eij, ++cij)
            *cij = *eij % mod;
    }
}
void mulOptimizedUnfoldImpl() {}
const int bsiz = 32;
Int64 F[bsiz][bsiz], G[bsiz][bsiz];
void mulOptimizedBlockImpl() {}
void mulOptimizedBlock() {}
#define test(func)                                 \
    {                                              \
        memset(C, 0, sizeof(C));                   \
        {                                          \
            Timer guard(#func);                    \
            func();                                \
        }                                          \
        puts(memcmp(C, D, sizeof(C)) == 0 ? "AC" : \
                                            "WA"); \
    }

int main() {
    std::random_device rd;
    std::uniform_int_distribution<int> gen(0, mod - 1);
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            A[i][j] = gen(rd);
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            B[i][j] = gen(rd);
    mulStandard();
    memcpy(D, C, sizeof(C));
    test(mulStandard);
    test(mulOptimizedMod);
    test(mulOptimizedCache);
    while(true)
        getchar();
    return 0;
}
