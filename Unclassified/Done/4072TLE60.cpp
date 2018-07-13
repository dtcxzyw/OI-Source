#include <cstdio>
#include <cstring>
const int size=3100;
int S[size];
long long dp[size][size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&S[i]);
		S[i]+=S[i-1];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j)
			for(int k=0;k<j;++k){
				long long len=S[j]-S[k];
				long long val=dp[i-1][k]+len*len;
				if(dp[i][j]>val)dp[i][j]=val;
			}
	}
	long long ans=m*dp[m][n]-S[n]*S[n];
	printf("%lld\n",ans);
	return 0;
}

