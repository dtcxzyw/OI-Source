#include <cstdio>
long long f[2000001];
int main(){
	int n;
	scanf("%d",&n);
	long long ans=0;
	for(int i=n;i>=1;--i){
		f[i]=n/i;
		f[i]*=f[i];
		for(int j=i<<1;j<=n;j+=i)f[i]-=f[j];
		ans+=f[i]*i;
	}
	ans-=1LL*n*(n+1)/2;
	ans>>=1;
	printf("%lld\n",ans);
	return 0;
}

