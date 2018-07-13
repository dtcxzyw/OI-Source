#include <bits/stdc++.h>
using namespace std;
int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
#define ll long long

const ll Max = 200033;
const ll inf = 9999999999999999ll;
ll n, m, now, K;
ll dis[Max], pos[Max], len[Max], Ans;
int bin[20], Log[Max];

struct Data {
    ll mn, id;
    Data() {}
    Data(ll a, ll b) {
        mn = a, id = b;
    }
};

void init() {
    bin[0] = 1;
    for (int i = 1; i <= 18; i++) {
        bin[i] = bin[i - 1] << 1;
        Log[bin[i]] = i;
    }
    for (int i = 1; i < Max; i++)
        if (!Log[i]) Log[i] = Log[i - 1];
}

struct ST {
    ll d[Max][18];
    void init() {
    	for (int j = 1; j <= Log[K]; j++)
    		for (int i = 1; i <= K; i++)
    			d[i][j] = min(d[i][j - 1], d[i + bin[j - 1]][j - 1]);
    }
    ll query(int L, int R) {
    	int len = R - L + 1;
    	return min(d[L][Log[len]], d[R - bin[Log[len]] + 1][Log[len]]);
    }
} st[2];

int tmp[Max], t[Max];

int lower(int V) {
	int L = 1, R = K, re = K + 1;
	while (R >= L) {
		int mid = (L + R) >> 1;
		if (tmp[mid] < V) L = mid + 1;
		else R = mid - 1, re = mid;
	}
	return re;
}

int upper(int V) {
	int L = 1, R = K, re = K + 1;
	while (R >= L) {
		int mid = (L + R) >> 1;
		if (tmp[mid] <= V) L = mid + 1;
		else R = mid - 1, re = mid;
	}
	return re;
}

void solve() {
    for (int i = 1; i <= K; i++)
        tmp[i] = pos[i];
    sort(tmp + 1, tmp + K + 1);
    for (int i = 1; i <= K; i++)
        t[tmp[i]] = i;
    for (int i = 1; i <= K; i++) {
    	st[0].d[t[pos[i]]][0] = len[i] - dis[pos[i]];
    	st[1].d[t[pos[i]]][0] = len[i] + dis[pos[i]];
    }
    st[0].init(), st[1].init();
    Ans = 0;
    for (int i = 1; i <= K; i++) {
        int ql = 1, qr = pos[i] - 1, L = pos[i], R = L;
        while (qr >= ql) {
            bool flag = 1;
            int mid = (ql + qr) >> 1;
            ll nowdis = len[i] + dis[pos[i]] - dis[mid], idx = pos[i] - mid;
            printf("dis %d ",(int)nowdis);
            ll dl = inf, dr = dl;
            
            int qql = lower(max(1ll, mid - idx));
            int qqr = upper(mid) - 1;
            if (qql <= qqr) dl = st[0].query(qql, qqr);
            printf("ll %d lr %d ",qql,qqr);
            
        	qql = lower(mid);
            qqr = upper(pos[i] - 1) - 1;
            if (qql <= qqr) dr = st[1].query(qql, qqr);
            printf("rl %d rr %d\n",qql,qqr);
            
            if (dl + dis[mid] <= nowdis) flag = 0;
            if (dr - dis[mid] <= nowdis) flag = 0;
            if (flag) qr = mid - 1, L = mid;
            else ql = mid + 1;
        }
        
        ql = pos[i] + 1, qr = n;
        while (qr >= ql) {
            bool flag = 1;
            int mid = (ql + qr) >> 1;
            ll nowdis = len[i] + dis[mid] - dis[pos[i]], idx = mid - pos[i];
            ll dl = inf, dr = dl;
            printf("dis %d ",(int)nowdis);
            
            int qql = lower(mid);
            int qqr = upper(min(mid + idx - 1, n)) - 1;
            if (qql <= qqr) dr = st[1].query(qql, qqr);
            printf("rl %d rr %d ",qql,qqr);
            
            qql = lower(pos[i] + 1);
            qqr = upper(mid) - 1;
            if (qql <= qqr) dl = st[0].query(qql, qqr);
            printf("ll %d lr %d\n",qql,qqr);
            
            if (dl + dis[mid] <= nowdis) flag = 0;
            if (dr - dis[mid] <= nowdis) flag = 0;
            if (mid + idx <= n) {
            	qqr = upper(min(mid + idx, n)) - 1;
            	if (tmp[qqr] == mid + idx)
            		if (st[1].d[qqr][0] - dis[mid] < nowdis)
            			flag = 0;
        	}
            if (flag) ql = mid + 1, R = mid,puts("XX");
            else qr = mid - 1;
        }
        Ans += (R - L + 1);
        printf("%d %d %d\n",i,L,R);
    }
    printf("%lld\n", Ans);
}

int main() {
    init();
    n = read(), m = read();
    for (int i = 2; i <= n; i++)
        dis[i] = dis[i - 1] + read();
    for (int i = 1; i <= m; i++) {
        K = read();
        for (int j = 1; j <= K; j++)
            pos[j] = read(), len[j] = read();
        solve();
    }
}

