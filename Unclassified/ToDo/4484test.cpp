#include <cstdio>
#include <algorithm>
#include <cstring>
const int size=30;
int A[size],dp[size];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		A[i]=i;
	int a=0,b=0;
	do{
		memset(dp,0,sizeof(dp));
		dp[0]=0;
		for(int i=1;i<=n;++i)
			for(int j=0;j<A[i];++j)
				dp[A[i]]=std::max(dp[A[i]],dp[j]+1);
		++a;
		int res=0;
		for(int i=1;i<=n;++i)
			res=std::max(res,dp[i]);
		b+=res;
		//for(int i=1;i<=n;++i)printf("%d ",A[i]);
		printf("%d\n",res);
	}while(std::next_permutation(A+1,A+n+1));
	printf("%lf\n",1.0*b/a);
	return 0;
}

