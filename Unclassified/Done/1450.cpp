#include <cstdio>
long long dp[100001]={};
int main(){
	int c[4],tot;
	scanf("%d%d%d%d%d",&c[0],&c[1],&c[2],&c[3],&tot);
	dp[0]=1;
	for(int k=0;k<4;++k)
		for(int i=c[k];i<=100000;++i)
			dp[i]+=dp[i-c[k]];

	for(int i=0;i<tot;++i){
		int d[4],s;
		scanf("%d%d%d%d%d",&d[0],&d[1],&d[2],&d[3],&s);
		long long ans=0;
		for(int j=0;j<16;++j){
			int p=s,cnt=1;
			for(int k=0;k<4;++k)if(j&(1<<k))p-=c[k]*(d[k]+1),++cnt;
			if(p<0)continue;
			if(cnt&1)ans+=dp[p];
			else ans-=dp[p];
		}
		printf("%lld\n",ans);
	}
	return 0;
}

