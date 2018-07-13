#include <cstdio>
#include <algorithm>
int a[201],sum[201],dp[201][201];
int query(int l,int r){
	return sum[r]-sum[l-1];
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
		dp[i][i]=a[i];
	}
	for(int k=1;k<n;++k)
		for(int i=1;i+k<=n;++i){
			int j=i+k;
			dp[i][j]=std::max(a[i]+query(i+1,j)-dp[i+1][j],a[j]+query(i,j-1)-dp[i][j-1]);
		}
	int s1=dp[1][n],s2=sum[n]-dp[1][n];
	printf("%d %d\n",s1,s2);
	return 0;
}

