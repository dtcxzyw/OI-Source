#include <cstdio>
long long dp[10][90][512]={};
int len[512]={};
int main(){
	int n,k,mst;
	scanf("%d%d",&n,&k);
	mst=1<<n;
	for(int i=0;i<mst;++i){
		int x=i;
		while(x){
			++len[i];
			x-=x&-x;
		}
	}
	
	dp[0][0][0]=1;
	
	for(int i=1;i<=n;++i)
		for(int j=0;j<=k;++j){
			for(int t=0;t<mst;++t){
				if(len[t]>j)continue;
				if(t&(t<<1))continue;
				for(int s=0;s<mst;++s){
					if(t&s)continue;
					if(s&(s<<1))continue;
					if(s&(t<<1))continue;
					if(t&(s<<1))continue;
					dp[i][j][t]+=dp[i-1][j-len[t]][s];
				}
			}
		}
	long long sum=0;
	for(int i=0;i<mst;++i)
		sum+=dp[n][k][i];
	printf("%lld\n",sum);
	return 0;
}

