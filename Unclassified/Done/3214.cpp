#include <cstdio>
#include <algorithm>
const int size=1000001,mod=100000007;
long long powm(long long a,int k){
	long long res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	long long powv=(powm(2,n)-1+mod)%mod;
	long long A=1,f1=1,f2=0,f3=0;
	for(int i=1;i<=m;++i){
		f3=f2;
		f2=f1;
		f1=(A-f2-f3*(i-1)%mod*(powv-(i-2))%mod)%mod;
		A=A*(powv-i+1)%mod;
	}
	long long fac=1;
	for(int i=1;i<=m;++i)fac=fac*i%mod;
	long long res=f1*powm(fac,mod-2)%mod;
	printf("%lld\n",(res%mod+mod)%mod);
	return 0;
}


