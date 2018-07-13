#include <cstdio>
int dp[1001][1001]={};
const int mod=10000;
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	dp[1][0]=1;
	for(int i=2;i<=n;++i){
		int end=i*(i-1)/2;
		dp[i][0]=1;
		for(int j=1;j<=end && j<=k;++j)
			dp[i][j]=(dp[i][j-1]+dp[i-1][j]+(j>=i?-dp[i-1][j-i]:0))%mod;
	}
	int ans=(dp[n][k]%mod+mod)%mod;
	printf("%d",ans);
	return 0;
}

