#include <cstdio>
const int mod=6662333;
long long powm(long long k){
	long long res=1,a=2;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
int main(){
	long long x;
	scanf("%lld",&x);
	printf("%lld\n",powm(x-1));
	return 0;
}

