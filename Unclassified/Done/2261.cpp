#include <cstdio>
#include <cmath>
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	long long ans=0,rk=sqrt(k);
	for(int i=1;i<=k/rk && i<=n;++i)
		ans+=k%i;
	for(int i=1;i<rk;++i){
		int b=k/(i+1)+1;
		int e=k/i;
		if(b<=n){
			if(e>n)e=n;
			ans+=1LL*(e-b+1)*(k%b+k%e)/2;
		}
	}
	if(n>k)ans+=1LL*(n-k)*k;
	printf("%lld\n",ans);
	return 0;
}

