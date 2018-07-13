#include <cstdio>
int read(int n){
	int res=0,c;
	for(int i=0;i<n;++i){
		scanf("%d",&c);
		res=res<<1|c;
	}
	return res;
}
const int mod=100000000;
int dp[13][1<<12],st[13];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)st[i]=read(m);
	dp[0][0]=1;
	int maxs=1<<m;
	for(int i=1;i<=n;++i)
		for(int j=0;j<maxs;++j){
			if((st[i]|j)!=st[i])continue;
			if(j&(j<<1))continue;
			for(int k=0;k<maxs;++k){
				if((st[i-1]|k)!=st[i-1])continue;
				if(k&(k<<1))continue;
				if(j&k)continue;
				dp[i][j]=(dp[i][j]+dp[i-1][k])%mod;	
			}
		}
	int ans=0;
	for(int i=0;i<maxs;++i)
		ans=(ans+dp[n][i])%mod;
	printf("%d\n",ans);
	return 0;
}

