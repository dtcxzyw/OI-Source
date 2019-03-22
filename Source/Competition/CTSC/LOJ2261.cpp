#include <cstdio>
const int size = 20000005;
bool p[size];
int seed, n, k, S;
int getrand() {
    seed = ((seed * 12321) ^ 9999) & 32767;
    return seed;
}
void generateData() {
    scanf("%d%d%d", &k, &seed, &S);
    int t = 0;
    n = k * 2 + 1;
    for(int i = 1; i <= n; ++i) {
        p[i] = (getrand() >> 7) & 1;
        t += p[i];
    }
    int i = 1;
    while(t > k) {
        while(!p[i])
            ++i;
        p[i] = 0;
        --t;
    }
    while(t < k) {
        while(p[i])
            ++i;
        p[i] = 1;
        ++t;
    }
}
int sum[size * 2], d[size * 2];
int main() {
    generateData();
    for(int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + (p[i] ? 1 : -1);
    for(int i = 1; i <= n; ++i)
        sum[i + n] = sum[i + n - 1] + (p[i] ? 1 : -1);
    int ans1 = 0, ans2 = 0, ans3 = 0, curA = 0;
    for(int i = 1; i < n; ++i)
        if(p[i]) {
            ++d[size + sum[i]];
            curA += (sum[i] > 0);
        }
    int NS = k - S;
    p[0] = p[n];
    for(int i = 1; i <= n; ++i) {
        if(p[i])
            curA -= d[size + sum[i]];
        else
            curA += d[size + sum[i - 1]];
        if(p[i])
            --d[size + sum[i]];
        if(p[i - 1]) {
            ++d[size + sum[i + n - 1]];
            curA += (sum[i + n - 1] > sum[i]);
        }
        if(!p[i]) {
            if(curA == 0)
                ans1 = i;
            if(curA == S)
                ans2 = i;
            if(curA == NS)
                ans3 = i;
        }
    }
    printf("%d\n%d\n%d\n", ans1, ans2, ans3);
    return 0;
}
