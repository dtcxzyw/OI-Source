#include <cstdio>
const int size=1000000,mod=1000000007;
int A[size],B[size];
int main(){
	int n,sum=0,ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&A[i]);
	for(int i=0;i<n;++i){
		B[i]=1LL*A[i]*sum%mod;
		sum=(sum+A[i])%mod;
	}
	sum=0;
	for(int i=0;i<n;++i){
		ans=(ans+1LL*A[i]*sum)%mod;
		sum=(sum+B[i])%mod;
	}
	printf("%lld\n",1LL*ans*6%mod);
	return 0;
}

