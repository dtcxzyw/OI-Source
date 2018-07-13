#include <cstdio>
const int size=50100,mod=10007;
int A[size];
bool check(int l,int n,int m){
	int len=0,cnt=0;
	for(int i=1;i<=n;++i)
		if(len+A[i]>l){
			len=A[i];
			if(m)--m;
			else return false;
		}
		else len+=A[i];
	return true;
}
void add(int& a,int b){
	a=(a+b)%mod;
}
int pre[size],sum[size],dp[2][size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int l=0,r=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&A[i]);
		if(A[i]>l)l=A[i];
		r+=A[i];
	}
	int ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,n,m))ans=mid,r=mid-1;
		else l=mid+1;
	}
	int now=1;
	sum[0]=0;
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1]+A[i];
		while(now<i && sum[i]-sum[now-1]>ans)++now;
		pre[i]=now;
	}
	for(int i=1;i<=n;++i)dp[1][i]=dp[1][i-1]+(sum[i]<=ans);
	int cnt=(sum[n]<=ans);
	for(int i=2;i<=m+1;++i){
		int c=i&1,l=c^1;
		dp[c][i-1]=0;
		for(int j=i;j<=n;++j)
			dp[c][j]=(dp[l][j-1]-(pre[j]==1?0:dp[l][pre[j]-2])+mod)%mod;
		add(cnt,dp[c][n]);
		for(int j=i;j<=n;++j)add(dp[c][j],dp[c][j-1]);
	}
	printf("%d %d\n",ans,cnt);
	return 0;
}

