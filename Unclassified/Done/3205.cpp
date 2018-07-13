#include <cstdio>
const int size=1001,mod=19650827;
int dp[size][size][2]={},A[size];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&A[i]);
		dp[i][i][0]=1;
	}
	for(int k=2;k<=n;++k)
		for(int r=k;r<=n;++r){
			int l=r-k+1;
			if(A[l]<A[l+1])dp[l][r][0]+=dp[l+1][r][0];
			if(A[l]<A[r])dp[l][r][0]+=dp[l+1][r][1];
			dp[l][r][0]%=mod;
			if(A[r]>A[l])dp[l][r][1]+=dp[l][r-1][0];
			if(A[r]>A[r-1])dp[l][r][1]+=dp[l][r-1][1];
			dp[l][r][1]%=mod;
		}
	printf("%d\n",(dp[1][n][0]+dp[1][n][1])%mod);
	return 0;
}

