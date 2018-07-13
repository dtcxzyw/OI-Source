#include <cstdio>
int dp[31][31]={};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	dp[0][0]=1;
	for(int i=1;i<=m;++i){
		for(int j=0;j<n;++j)
			dp[i][j]+=dp[i-1][(j+1)%n]+dp[i-1][(j-1+n)%n];
	}
	printf("%d\n",dp[m][0]);
	return 0;
}

