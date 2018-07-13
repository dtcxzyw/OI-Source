#include <cstdio>
const int mod=1000000007,size=10005;
int C[size][105];
void pre(int n,int m){
	C[0][0]=1;
	for(int i=1;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=m && j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int dp[16][size];
int main(){
	int n,k,d;
	scanf("%d%d%d",&n,&k,&d);
	++d;
	pre(n,k);
	int hk=k>>1,siz=n-k;
	dp[0][0]=1;
	for(int i=0;i<15;++i){
		for(int j=0;j<=siz;++j){
			for(int x=0;x*d<=hk && j+x*d*(1<<i)<=siz;++x){
				int val=x*d,&dst=dp[i+1][j+x*d*(1<<i)];
				dst=(dst+static_cast<long long>(dp[i][j])*C[hk][val])%mod;
			}
		}
	}
	int sub=0;
	for(int i=0;i<=siz;++i)sub=(sub+static_cast<long long>(dp[15][i])*C[n-i-hk][hk])%mod;
	int sum=C[n][k];
	printf("%d\n",(sum-sub+mod)%mod);
	return 0;
}

