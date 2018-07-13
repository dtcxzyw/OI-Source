#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int w[16],dp[1<<16],sum[100010];
int main(){
	int k=read();
	int n=read();
	for(int i=0;i<k;++i)w[i]=read();
	sum[0]=0;
	for(int i=1;i<=n;++i)sum[i]=sum[i-1]+read();
	int end=1<<k,ans=-1;
	dp[0]=0;
	for(int i=1;i<end;++i){
		for(int j=0;j<k;++j)
			if(i&(1<<j)){
				int src=i^(1<<j);
				int tot=sum[dp[src]]+w[j];
				int cnt=std::upper_bound(sum+dp[src],sum+n+1,tot)-sum-1;
				if(cnt>dp[i])dp[i]=cnt;
			}
		if(dp[i]==n){
			int tot=0;
			for(int j=0;j<k;++j)
				if(!(i&(1<<j)))
					tot+=w[j];
			if(ans<tot)ans=tot;
		}
	}
	printf("%d\n",ans);
	return 0;
}

