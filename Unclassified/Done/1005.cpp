#include <cstdio>
typedef long long int128;
int128 dp[81][81],A[81];
void print(int128 x){
	if(x>=10)print(x/10);
	putchar('0'+x%10);
}
int128 maxv(int128 a,int128 b){
	return a>b?a:b;
}
int main(){
	int n,m,x;
	scanf("%d%d",&n,&m);
	int128 ans=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&x);
			A[j]=dp[j][j]=x;
			dp[j][j]<<=m;
		}
		for(int k=2;k<=m;++k)
			for(int r=k;r<=m;++r){
				int l=r-k+1,sh=m-k+1;
				dp[l][r]=maxv((A[l]<<sh)+dp[l+1][r],(A[r]<<sh)+dp[l][r-1]);
			}
		ans+=dp[1][m];
	}
	print(ans);
	return 0;
}

