#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
typedef long long HashT;
HashT hash(const std::vector<int>& A) {
    HashT res = 0;
    for(int i = 0; i < A.size(); ++i)
        res = res * 131 + A[i];
    return res;
}
std::map<HashT, int> cache;
int minl, maxl;
int DFS(const std::vector<int>& A) {
    HashT hv = hash(A);
    // std::map<HashT, int>::iterator it =
    // cache.find(hv);
    // if(it != cache.end())
    // return it->second;
    int& res = cache[hv];
    for(int i = 0, j = 0; i < A.size(); i = j) {
        int c = A[i];
        while(j < A.size() && c == A[j])
            ++j;
        for(int k = std::min(i + maxl, j);
            k >= i + minl; --k) {
            int siz = k - i;
            if(siz * siz +
                   (A.size() - siz) *
                       (A.size() - siz) <=
               res)
                continue;
            std::vector<int> cur;
            cur.reserve(A.size() - siz);
            cur.insert(cur.end(), A.begin(),
                       A.begin() + i);
            cur.insert(cur.end(), A.begin() + k,
                       A.end());
            res = std::max(res, siz * siz + DFS(cur));
        }
    }
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> A;
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        A.push_back(x);
    }
    scanf("%d%d", &minl, &maxl);
    printf("%d\n", DFS(A));
    return 0;
}
