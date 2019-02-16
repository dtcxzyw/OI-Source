#pragma once
#include "TestLib.hpp"
#include <algorithm>
#include <cstring>
#include <vector>
using Int64 = long long;
#define asInt64 static_cast<Int64>
constexpr int mod = 998244353, size = 1 << 23;
int add(int a, int b) {
    a += b;
    return a < mod ? a : a - mod;
}
int sub(int a, int b) {
    a -= b;
    return a >= 0 ? a : a + mod;
}
int clamp(int a) {
    return a >= 0 ? a : a + mod;
}
Int64 powm(Int64 a, int k) {
    Int64 res = 1;
    while(k) {
        if(k & 1)
            res = res * a % mod;
        k >>= 1, a = a * a % mod;
    }
    return res;
}
int root[size], invR[size];
void init() {
    Int64 base = powm(3, (mod - 1) / size);
    Int64 invBase = powm(base, mod - 2);
    root[0] = invR[0] = 1;
    for(int i = 1; i < size; ++i)
        root[i] = root[i - 1] * base % mod;
    for(int i = 1; i < size; ++i)
        invR[i] = invR[i - 1] * invBase % mod;
}
void NTT(int n, int* A, const int* w) {
    for(int i = 0, j = 0; i < n; ++i) {
        if(i < j)
            std::swap(A[i], A[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }
    for(int i = 2; i <= n; i <<= 1) {
        int m = i >> 1, fac = size / i;
        for(int j = 0; j < n; j += i)
            for(int k = 0, kp = 0; k < m;
                ++k, kp += fac) {
                int &x = A[j + k], &y = A[j + k + m];
                int t = asInt64(w[kp]) * y % mod;
                y = sub(x, t);
                x = add(x, t);
            }
    }
}
int getSize(int n) {
    n <<= 1;
    int p = 1;
    while(p < n)
        p <<= 1;
    return p;
}
using Poly = std::vector<int>;
void copy(Poly& dst, const Poly& src, int siz) {
    memcpy(dst.data(), src.data(), sizeof(int) * siz);
}
void DFT(int n, Poly& A) {
    NTT(n, A.data(), root);
}
void IDFT(int n, Poly& A, int rn) {
    NTT(n, A.data(), invR);
    Int64 div = powm(n, mod - 2);
    for(int i = 0; i < rn; ++i)
        A[i] = A[i] * div % mod;
    memset(A.data() + rn, 0, sizeof(int) * (n - rn));
}
Clock::duration benchmarkNTT(int n) {
    int p = getSize(n);
    puts("Generating input data for NTT...");
    Poly A = genData(p, p, mod);
    puts("Calculating NTT...");
    Clock::duration t =
        time([&] { NTT(p, A.data(), root); });
    puts("Done.");
    return t;
}
struct WrongAnswer {};
