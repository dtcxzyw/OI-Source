#include <cstdio>
const int mod=9901;
int dp[101][201]={};
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;++i)
		dp[i][1]=1;
	
	for(int i=2;i<=k;++i)
		for(int j=1;j<=n;j+=2)
				for(int l=1;l<j;l+=2){
					int r=j-1-l;
					dp[i][j]=(dp[i][j]+dp[i-1][l]*dp[i-1][r])%mod;
				}
				
	printf("%d\n",(dp[k][n]-dp[k-1][n]+mod)%mod);
	return 0;
}

