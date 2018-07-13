#include <cstdio>
int dp[2][4300]={};
int main(){
	int n,p;
	scanf("%d%d",&n,&p);
	dp[1][1]=1;
	for(int i=2;i<=n;++i){
		int c=i&1,l=c^1;
		for(int j=1;j<=i;++j)
			dp[c][j]=(dp[c][j-1]+dp[l][i-j+1])%p;
	}
	int res=0;
	for(int i=1;i<=n;++i)
		res=(res+dp[n&1][i])%p;
	printf("%d\n",(res<<1)%p);
	return 0;
}

