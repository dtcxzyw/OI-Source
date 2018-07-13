#include <cstdio>
const int mod=1000000009;
int dp[10001][100]={},prime[1001],cnt=0;
bool isPrime(int x){
	for(int i=2;i*i<=x;++i)
		if(x%i==0)
			return false;
	return true;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=101;i<1000;++i)
		if(isPrime(i)){
			prime[cnt++]=i;
			++dp[3][i%100];
		}
		
	for(int i=4;i<=n;++i)
		for(int j=0;j<cnt;++j){
			int p=prime[j];
			dp[i][p%100]=(dp[i][p%100]+dp[i-1][p/10])%mod;
		}
		
	int ans=0;
	for(int i=0;i<100;++i)
			ans=(ans+dp[n][i])%mod;
	printf("%d\n",ans);
	return 0;
}

