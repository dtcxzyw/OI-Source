#include <cstdio>
#include <algorithm>
#include <cstring>
int v[21],g[101],dp[100001];
int main(){
	int n,b;
	scanf("%d%d",&n,&b);
	for(int i=1;i<=b;++i)
		scanf("%d",&v[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&g[i]);
	int maxg=0;
	for(int i=n;i>=1;--i){
		g[i]-=std::max(g[i-1]-1,0);
		maxg=std::max(maxg,g[i]);
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=b;++i)
		for(int j=v[i];j<=maxg;++j)
			dp[j]=std::min(dp[j],dp[j-v[i]]+1);
	int ans=0;
	for(int i=1;i<=n;++i){
		if(dp[g[i]]==0x3f3f3f3f){
			puts("-1");
			return 0;
		}
		ans+=dp[g[i]];
	}
	printf("%d\n",ans);
	return 0;
}

