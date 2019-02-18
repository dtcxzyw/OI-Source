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
using NTTFac = std::vector<int>;
NTTFac root[24], invR[24], rev[24];
void initImpl(int k) {
    int siz = 1 << k;
    Int64 base = powm(3, (mod - 1) / siz);
    Int64 invBase = powm(base, mod - 2);
    NTTFac &rt = root[k], &irt = invR[k];
    rt.resize(siz), irt.resize(siz);
    rt[0] = irt[0] = 1;
    for(int i = 1; i < siz; ++i)
        rt[i] = rt[i - 1] * base % mod;
    for(int i = 1; i < siz; ++i)
        irt[i] = irt[i - 1] * invBase % mod;
    NTTFac& A = rev[k];
    A.resize(siz);
    int off = k - 1;
    for(int i = 0; i < siz; ++i)
        A[i] = A[i >> 1] >> 1 | ((i & 1) << off);
}
void init() {
    for(int i = 0; i < 24; ++i)
        initImpl(i);
}
void NTT(int n, int* A, const NTTFac* w) {
    int p = 0;
    while(1 << p != n)
        ++p;
    NTTFac& R = rev[p];
    for(int i = 0; i < n; ++i)
        if(i < R[i])
            std::swap(A[i], A[R[i]]);
    for(int i = 2, cp = 1; i <= n; i <<= 1, ++cp) {
        int m = i >> 1;
        const NTTFac& fac = w[cp];
        for(int j = 0; j < n; j += i)
            for(int k = 0; k < m; ++k) {
                int &x = A[j + k], &y = A[j + m + k];
                int t = asInt64(fac[k]) * y % mod;
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
void shift(Poly& A, int h, int n) {
    Poly B(A.size());
    memcpy(B.data(), A.data() + h,
           sizeof(int) * (n - h));
    memcpy(B.data() + (n - h), A.data(),
           sizeof(int) * h);
    A.swap(B);
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
Duration benchmarkNTT(int n) {
    int p = getSize(n);
    puts("Generating input data for NTT...");
    Poly A = genData(p, p, mod);
    puts("Calculating NTT...");
    Duration t = time([&] { NTT(p, A.data(), root); });
    puts("Done.");
    return t;
}
struct WrongAnswer {};
