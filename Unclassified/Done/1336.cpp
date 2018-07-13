#include <cstdio>
#include <cstring>
long long dp[201];
int A[21],B[21];
void CAS(long long& a,long long b){
	if(a>b)a=b;
}
long long ipow(int a,int k){
	long long res=1;
	while(k--)res*=a;
	return res;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=m;++i)
		scanf("%d%d",&A[i],&B[i]);
		
	for(int i=1;i<=m;++i)
		for(int j=n;j>=1;--j)
			for(int k=1;k<=j;++k){
				long long t=A[i]*ipow(k,B[i]);		
				CAS(dp[j],dp[j-k]+t);
			}

	printf("%lld\n",dp[n]);
	return 0;
}

