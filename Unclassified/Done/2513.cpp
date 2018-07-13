#include <cstdio>
int dp[1001][1001]={};
void add(int& a,int b){
	a=(a+b)%10000;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	dp[1][0]=1;
	for(int i=1;i<n;++i){
		int end=i*(i-1)/2;
		for(int j=0;j<=end;++j)
			for(int a=0;a<=i && j+a<=k;++a)
				add(dp[i+1][j+a],dp[i][j]);
	}
	printf("%d",dp[n][k]);
	return 0;
}

