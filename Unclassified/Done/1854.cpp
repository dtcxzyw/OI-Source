#include <cstdio>
#include <cstring>
int A[101][101],dp[101][101],pre[101][101],p[101];
void CAS(int& a,int b,int& c,int d){
	if(a<b)a=b,c=d;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&A[i][j]);
	memset(dp,0xc0,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=i;j<=m;++j)
			for(int k=i-1;k<j;++k)
				CAS(dp[i][j],dp[i-1][k]+A[i][j],pre[i][j],(i-1)*1000+k);
	int ans=-1<<30,end;
	for(int i=n;i<=m;++i)
		CAS(ans,dp[n][i],end,n*1000+i);
	printf("%d\n",ans);
	for(int i=n;i>=1;--i){
		p[i]=end%1000;
		end=pre[end/1000][end%1000];
	}
	for(int i=1;i<=n;++i)
		printf("%d ",p[i]);
	return 0;
}

