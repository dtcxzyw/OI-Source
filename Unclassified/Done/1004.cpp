#include <cstdio>
int w[10][10],dp[10][10][10][10]={};
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n;
	scanf("%d",&n);
	int x,y;
	while(true){
		scanf("%d%d",&x,&y);
		if(x&&y)scanf("%d",&w[x][y]);
		else break;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)
				for(int l=1;l<=n;++l){
					int add=w[i][j];
					if(i!=k || j!=l)add+=w[k][l];
					CAS(dp[i][j][k][l],dp[i-1][j][k-1][l]+add);
					CAS(dp[i][j][k][l],dp[i-1][j][k][l-1]+add);
					CAS(dp[i][j][k][l],dp[i][j-1][k-1][l]+add);
					CAS(dp[i][j][k][l],dp[i][j-1][k][l-1]+add);
				}
				
	printf("%d\n",dp[n][n][n][n]);
	return 0;
}

