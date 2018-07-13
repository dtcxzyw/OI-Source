#include <cstdio>
const int mod=100003;
long long powm(long long a,long long k){
	a%=mod;
	long long res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
long long clamp(long long x){
	return (x%mod+mod)%mod;
}
int main(){
	long long m,n;
	scanf("%lld%lld",&m,&n);
	printf("%lld\n",(m%mod)*clamp(powm(m,n-1)-powm(m-1,n-1))%mod);
	return 0;
}

