#include <cstdio>
#include <algorithm>
const int size=1000001,mod=100000007;
int dp[100][60][100]={};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	dp[0][0][0]=1;
	int end=1<<n;
	for(int i=1;i<end;++i){
		for(int j=0;j<=m;++j)
			for(int k=0;k<end;++k)
				dp[i][j][k]+=dp[i-1][j-1][k^i]+dp[i-1][j][k];
	}
	printf("%d\n",dp[end-1][m][0]);
	return 0;
}


