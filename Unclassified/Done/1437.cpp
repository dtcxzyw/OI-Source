#include <cstdio>
#include <cstring>
int mat[60][60],dp[2][60][1300]={};
int maxv(int a,int b){
	return a>b?a:b;
}
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n,m,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n-i+1;++j)
			scanf("%d",&mat[i][j]);
	for(int i=n;i>=1;--i){
		int c=i&1,l=!c,sum=0;
		memset(dp[c],0,sizeof(dp[c]));
		for(int j=1;j<=n-i+1;++j)sum+=mat[j][i];
		for(int j=n-i+1;j>=0;--j){
			for(int k=maxv(2*j-1,0);k<=m;++k){
				CAS(dp[c][j][k],maxv(dp[c][j+1][k],dp[l][maxv(j-1,0)][k-j]+sum));
				CAS(ans,dp[c][j][k]);
			}
			sum-=mat[j][i];
		}
	}
	printf("%d\n",ans);
	return 0;
}

