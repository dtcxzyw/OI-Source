#include <cstdio>
#include <cstring>
const int size = 100005, s = 12;
int cache[size];
int SG1(int x) {
    if(x == 0)
        return 0;
    if(cache[x] != -1)
        return cache[x];
    bool use[size] = {};
    for(int i = 1; i <= x; ++i)
        use[SG1(x - i)] = true;
    for(int i = 0; i < size; ++i) {
        if(!use[i]) {
            cache[x] = i;
            return i;
        }
    }
    throw;
}
int SG1Fast(int x) {
    return x;
}
int SG2(int x) {
    if(x == 0)
        return 0;
    if(cache[x] != -1)
        return cache[x];
    bool use[size] = {};
    for(int i = 1; i <= x; i *= s)
        use[SG2(x - i)] = true;
    for(int i = 0; i < size; ++i) {
        if(!use[i]) {
            cache[x] = i;
            return i;
        }
    }
    throw;
}
int SG2Fast(int x) {
    if(s & 1)
        return x & 1;
    int val = x % (s + 1);
    if(val == s)
        return 2;
    return val % 2;
}
int SG3(int x) {
    if(x == 0)
        return 0;
    if(cache[x] != -1)
        return cache[x];
    bool use[size] = {};
    for(int i = s; i <= x; ++i)
        use[SG3(x - i)] = true;
    for(int i = 0; i < size; ++i) {
        if(!use[i]) {
            cache[x] = i;
            return i;
        }
    }
    throw;
}
int SG3Fast(int x) {
    return x / s;
}
int SG4(int x) {
    if(x == 0)
        return 0;
    if(cache[x] != -1)
        return cache[x];
    bool use[size] = {};
    for(int i = 1; i <= x; ++i)
        use[SG4(x - i)] = true;
    for(int i = 1; i < x; ++i)
        use[SG4(i) ^ SG4(x - i)] = true;
    for(int i = 0; i < size; ++i) {
        if(!use[i]) {
            cache[x] = i;
            return i;
        }
    }
    throw;
}
int SG4Fast(int x) {
    if(x == 0)
        return 0;
    if(x % 4 == 3)
        return x + 1;
    if(x % 4 == 0)
        return x - 1;
    return x;
}
int main() {
    memset(cache, -1, sizeof(cache));
    for(int i = 0; i <= 100000; ++i) {
        int va = SG2(i), vb = SG2Fast(i);
        printf("%d %d %d\n", i, va, vb);
        if(va != vb)
            throw;
    }
    return 0;
}
