#include <cstdio>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=1010;
int A[size][size];
long long dp[size][size];
long long maxv(long long a,long long b){
	return a>b?a:b;
}
long long foo(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			A[i][j]=read();
	for(int i=1;i<=n;++i)
		for(int j=m;j>=1;--j)
			dp[i][j]=maxv(dp[i-1][j+1]+A[i][j],maxv(dp[i-1][j],dp[i][j+1]));
	return dp[n][1];
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)printf("%lld\n",foo());
	return 0;
}

