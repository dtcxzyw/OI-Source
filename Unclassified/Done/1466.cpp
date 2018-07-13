#include <cstdio>
long long dp[1000]={};
int main(){
	int n;
	scanf("%d",&n);
	int sum=(n*(n+1))>>1;
	if(sum&1)puts("0");
	else{
		sum>>=1;
		dp[0]=1;
		for(int i=1;i<=n;++i)
			for(int j=sum;j>=i;--j)
				dp[j]+=dp[j-i];
		printf("%lld\n",dp[sum]>>1);
	}
	return 0;
}

