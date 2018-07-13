#include <cstdio>
const int mod=20100403,size=2000100;
long long fac[size],ifac[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	fac[0]=ifac[0]=ifac[1]=1;
	int end=n+m;
	for(int i=1;i<=end;++i)
		fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<=end;++i)
		ifac[i]=(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=2;i<=end;++i)
		ifac[i]=ifac[i-1]*ifac[i]%mod;
	long long A=(fac[n+m]*ifac[n]%mod)*ifac[m]%mod;
	long long B=(fac[n+m]*ifac[n+1]%mod)*ifac[m-1]%mod;
	printf("%lld\n",(A-B+mod)%mod);
	return 0;
}

