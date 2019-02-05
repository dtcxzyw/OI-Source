#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
int read() {
    int res = 0, c;
    do
        c = getchar();
    while(c < '0' || c > '9');
    while('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}
typedef long long Int64;
const int size = 300005;
struct Set {
    std::vector<int> A;
    int key;
} S[size];
int id[size];
struct State {
    int i, j;
    Int64 sum;
    State(int i, int j, Int64 sum)
        : i(i), j(j), sum(sum) {}
    bool operator<(const State& rhs) const {
        return sum < rhs.sum;
    }
};
bool cmpG(int a, int b) {
    return a > b;
}
bool cmpS(int a, int b) {
    return S[a].key < S[b].key;
}
int main() {
    int n = read();
    int k = read();
    Int64 sum = 0;
    for(int i = 1; i <= n; ++i) {
        int c = read();
        std::vector<int>& A = S[i].A;
        A.resize(c);
        for(int j = 0; j < c; ++j)
            A[j] = read();
        std::sort(A.begin(), A.end(), cmpG);
        if(c == 1)
            S[i].key = 1 << 30;
        else
            S[i].key = A[0] - A[1];
        sum += A[0];
        id[i] = i;
    }
    std::sort(id + 1, id + n + 1, cmpS);
    std::priority_queue<State> heap;
    if(S[id[1]].A.size() == 1) {
        heap.push(State(1, 0, sum));
    } else {
        --k;
        printf("%lld ", sum);
        heap.push(State(1, 1, sum - S[id[1]].key));
    }
    for(int i = 1; i <= k; ++i) {
        State cur = heap.top();
        heap.pop();
        printf("%lld ", cur.sum);
        int cs = id[cur.i], ns = id[cur.i + 1];
        if(cur.j + 1 < S[cs].A.size())
            heap.push(State(cur.i, cur.j + 1, cur.sum -
                                S[cs].A[cur.j] +
                                S[cs].A[cur.j + 1]));
        if(cur.i < n && S[ns].A.size() >= 2) {
            heap.push(State(cur.i + 1, 1,
                            cur.sum - S[ns].key));
            if(cur.j == 1)
                heap.push(State(cur.i + 1, 1, cur.sum +
                                    S[cs].key -
                                    S[ns].key));
        }
    }
    return 0;
}
