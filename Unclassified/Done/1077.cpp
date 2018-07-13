#include <cstdio>
const int mod=1000007;
int A[105],dp[105][105]={};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&A[i]);
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j)
			for(int k=0;k<=A[i] && k<=j;++k)
				dp[i][j]=(dp[i][j]+dp[i-1][j-k])%mod;
	printf("%d\n",dp[n][m]);
	return 0;
}

