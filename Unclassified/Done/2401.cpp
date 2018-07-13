#include <cstdio>
int dp[1001][1001];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<=n;++i)dp[i][0]=1;
	for(int i=2;i<=n;++i)
		for(int j=1;j<=k && j<i;++j)
			dp[i][j]=(dp[i-1][j]*(j+1)+dp[i-1][j-1]*(i-j))%2015;
	printf("%d\n",dp[n][k]);
	return 0;
}

