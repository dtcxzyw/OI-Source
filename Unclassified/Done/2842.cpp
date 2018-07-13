#include <cstdio>
long long powm(long long a,long long k,long long m){
	a%=m;
	long long res=1;
	while(k){
		if(k&1)res=res*a%m;
		k>>=1,a=a*a%m;
	}
	return res;
}
const long long P=1000000007LL;
int main(){
	long long a,b;
	scanf("%lld%lld",&a,&b);
	//a#b=a^(a^(b-1))
	//a^(p-1) mod P =1
	//a#b mod P = a^(a^(b-1) mod (P-1)) mod P
	long long k=powm(a,b-1,P-1);
	long long res=powm(a,k,P);
	printf("%lld\n",res);
	return 0;
}

