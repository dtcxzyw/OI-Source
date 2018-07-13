#include <cstdio>
int dp[51][51][51][51]={},w[51][51];
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&w[i][j]);
			
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=n;++k)
				for(int l=1;l<=m;++l){
					int add=w[i][j];
					if(i!=k || j!=l)add+=w[k][l];
					CAS(dp[i][j][k][l],dp[i-1][j][k-1][l]+add);
					CAS(dp[i][j][k][l],dp[i-1][j][k][l-1]+add);
					CAS(dp[i][j][k][l],dp[i][j-1][k-1][l]+add);
					CAS(dp[i][j][k][l],dp[i][j-1][k][l-1]+add);
				}
				
	printf("%d\n",dp[n][m][n][m]);
	return 0;
}

