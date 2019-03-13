#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long Int64;
#define asInt64 static_cast<Int64>
bool LUT[505][505];
bool gcd(int a, int b) {
    if(a <= 500 && b <= 500)
        return LUT[a][b];
    return b ? gcd(b, a % b) : a != 1;
}
const int size = 100005;
int p[size], mu[size];
bool flag[size];
void pre(int n) {
    mu[1] = 1;
    int pcnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!flag[i]) {
            p[++pcnt] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= pcnt && i * p[j] <= n;
            ++j) {
            int val = i * p[j];
            flag[val] = true;
            if(i % p[j])
                mu[val] = -mu[i];
            else
                break;
        }
    }
}
Int64 fa[size], fb[size], fc[size];
struct Info {
    int x, y, z;
    Info() {}
    Info(int x, int y, int z) : x(x), y(y), z(z) {}
} X[size * 8];
std::vector<std::pair<int, int> > G[size];
int d[size], vis[size];
Int64 foo(int A, int B, int C) {
    int end = std::max(A, std::max(B, C));
    for(int i = 1; i <= end; ++i) {
        fa[i] = fb[i] = fc[i] = 0;
        for(int j = i; j <= end; j += i)
            fa[i] += A / j, fb[i] += B / j,
                fc[i] += C / j;
    }
    Int64 res = 0;
    // i i i
    for(int i = 1; i <= end; ++i)
        if(mu[i]) {
            Int64 delta = fa[i] * fb[i] * fc[i];
            res += (mu[i] < 0 ? -delta : delta);
        }
    // x=ij y=ik x x y/x y y
    int ecnt = 0;
    for(int i = 1; i <= end; ++i)
        d[i] = 0;
    for(int i = 1; i <= end; ++i)
        for(int j = 1, x = i; x * (j + 1) <= end;
            ++j, x += i) {
            if(mu[x] == 0)
                continue;
            for(int k = j + 1, y = i * k, z = x * k;
                z <= end; ++k, y += i, z += x) {
                if(gcd(j, k) || mu[y] == 0)
                    continue;
                Int64 bc = fb[z] * fc[z],
                      ac = fa[z] * fc[z],
                      ab = fa[z] * fb[z];
                Int64 da = mu[y] * fa[x] +
                    mu[x] * fa[y],
                      db = mu[y] * fb[x] +
                    mu[x] * fb[y],
                      dc = mu[y] * fc[x] +
                    mu[x] * fc[y];
                res += da * bc + db * ac + dc * ab;
                X[++ecnt] = Info(x, y, z);
                ++d[x], ++d[y];
            }
        }
    // i j k
    for(int i = 1; i <= end; ++i)
        G[i].clear();
    for(int i = 1; i <= ecnt; ++i) {
        Info E = X[i];
        if(d[E.x] > d[E.y] ||
           (d[E.x] == d[E.y] && E.x < E.y))
            std::swap(E.x, E.y);
        G[E.x].push_back(std::make_pair(E.y, E.z));
    }
    for(int i = 1; i <= end; ++i) {
        for(int j = 0; j < G[i].size(); ++j) {
            int y = G[i][j].first, z = G[i][j].second;
            vis[y] = z;
        }
        for(int j = 0; j < G[i].size(); ++j) {
            int v = G[i][j].first, x = G[i][j].second;
            for(int k = 0; k < G[v].size(); ++k) {
                int w = G[v][k].first,
                    y = G[v][k].second;
                int fac = mu[i] * mu[v] * mu[w];
                int z = vis[w];
                if(z == 0)
                    continue;
                Int64 delta =
                    (fa[x] * fb[y] + fa[y] * fb[x]) *
                        fc[z] +
                    (fb[x] * fc[y] + fb[y] * fc[x]) *
                        fa[z] +
                    (fa[x] * fc[y] + fa[y] * fc[x]) *
                        fb[z];
                res += (fac < 0 ? -delta : delta);
            }
        }
        for(int j = 0; j < G[i].size(); ++j) {
            int y = G[i][j].first;
            vis[y] = 0;
        }
    }
    return res;
}
bool pgcd(int a, int b) {
    return b ? pgcd(b, a % b) : a != 1;
}
int main() {
    for(int i = 0; i <= 500; ++i)
        for(int j = 0; j <= 500; ++j)
            LUT[i][j] = pgcd(i, j);
    pre(100000);
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i) {
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        printf("%lld\n", foo(A, B, C) % 1000000007);
    }
    return 0;
}
