#include <cstdio>
int dp[310][151][21][21]={};
void add(int& a,int b){
	a=(a+b)%12345678;
}
int maxv(int a,int b){
	return a>b?a:b;
}
int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	dp[0][0][0][0]=1;
	for(int i=0;i<n+m;++i)
		for(int j=0;j<=n && j<=i;++j)
			for(int x=0;x<=k;++x)
				for(int y=0;y<=k;++y)
					if(dp[i][j][x][y]){
						if(j+1<=n && x+1<=k)add(dp[i+1][j+1][x+1][maxv(y-1,0)],dp[i][j][x][y]);
						if(i-j+1<=m && y+1<=k)add(dp[i+1][j][maxv(x-1,0)][y+1],dp[i][j][x][y]);
					}
	int ans=0;
	for(int i=0;i<=k;++i)
		for(int j=0;j<=k;++j)
			add(ans,dp[n+m][n][i][j]);
	printf("%d\n",ans);
	return 0;
}

