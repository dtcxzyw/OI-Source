#include <cstdio>
const int size=5000;
long long dp[size][size]={};
int main(){
	int A,n,mod;
	scanf("%d%d%d",&A,&n,&mod);	
	for(int i=0;i<=A;++i)dp[0][i]=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=A;++j)
			dp[i][j]=(dp[i-1][j-1]*j+dp[i][j-1])%mod;
	}
	long long res=dp[n][A];
	for(int i=1;i<=n;++i)res=res*i%mod;
	printf("%lld\n",res);
	return 0;
}

