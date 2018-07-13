#include <cstdio>
#include <cmath>
const long long mod=998244353;
long long query(long long x){
	long long res=0,rtx=sqrt(x);
	for(long long i=1;i<=rtx;++i)
	    res=(res+i*(x/i-x/(i+1))%mod)%mod;
	for(long long i=1;i<=x/(rtx+1);++i)
	    res=(res+x/i)%mod;
	return res;
}
int main(){
	long long a,b;
	scanf("%lld%lld",&a,&b);
	printf("%lld\n",((query(b)-query(a-1))%mod+mod)%mod);
	return 0;
}

