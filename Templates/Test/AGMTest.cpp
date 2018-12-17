#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <random>
using REng = std::mt19937_64;
using Clock = std::chrono::high_resolution_clock;
using IntType = REng::result_type;
bool A[505][505];
bool test() {
    int n = 200;
    int m = 1000;
    REng rnd(Clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> uid(1, n);
    memset(A, 0, sizeof(A));
    puts("Gen");
    {
        std::ofstream out("input");
        out << n << " " << m << std::endl;
        for(int i = 1; i <= m; ++i) {
            while(true) {
                int u = uid(rnd), v = uid(rnd);
                if(u != v && !A[u][v]) {
                    out << u << " " << v << std::endl;
                    A[u][v] = A[v][u] = true;
                    break;
                }
            }
        }
    }
    puts("Test Std");
    system("./Blossom.out <input >out1");
    puts("Test AGM");
    system("./AGM.out <input >out2");
    puts("Check");
    std::ifstream o1("out1"), o2("out2");
    int a, b;
    o1 >> a, o2 >> b;
    printf("%d %d\n", a, b);
    return a == b;
}
int main() {
    int cnt = 0;
    while(test())
        printf("pass %d\n", ++cnt);
    printf("fail %d\n", ++cnt);
    return 0;
}
