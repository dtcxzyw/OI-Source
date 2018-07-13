#include <cstdio>
#include <cstring>
int sum[2501]={};
int iabs(int a){
	return a>0?a:-a;
}
bool query(int l,int r,int m){
	int w=iabs(sum[r]-sum[l-1]);
	return w==(r-l+1)||w<=m;
}
void CAS(int& a,int b){
	if(a>b)a=b;
}
int dp[2501];
int main(){
	int n,m,t;
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=n;++i){
		scanf("%d",&t);
		if(t==1)sum[i]=1;
		else sum[i]=-1;
	}
	for(int i=1;i<=n;++i)
		sum[i]+=sum[i-1];
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;++i){
		dp[i]=dp[i-1]+1;
		for(int j=0;j<i;++j)
			if(query(j+1,i,m))
				CAS(dp[i],dp[j]+1);
	}
	printf("%d\n",dp[n]);
	return 0;
}

