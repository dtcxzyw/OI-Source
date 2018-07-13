#include <cstdio>
int dp[60][270000]={};
int main(){
	int n,c;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){	
		scanf("%d",&c);
		dp[c][i]=i+1;
	}
	int ans=0;
	for(int i=2;i<60;++i)
		for(int j=1;j<=n;++j){
			if(!dp[i][j])dp[i][j]=dp[i-1][dp[i-1][j]];
			if(dp[i][j])ans=i;
		}
	printf("%d\n",ans);
	return 0;
}

