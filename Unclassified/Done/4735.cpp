#include <cstdio>
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size=1000005;
Int64 powm(Int64 a,Int64 k,int mod){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
Int64 fac(Int64 n,int p,int pk){
	if(n==0)return 1;
	Int64 res=1;
	for(int i=2;i<=pk;++i)if(i%p)res=res*i%pk;
	res=powm(res,n/pk,pk);
	int rem=n%pk;
	for(int i=2;i<=rem;++i)if(i%p)res=res*i%pk;
	return res?res*fac(n/p,p,pk)%pk:0;
}
Int64 lucas(Int64 n,Int64 m,int p,int pk){
	if(n<m)return 0;
	Int64 a=fac(n,p,pk),b=fac(m,p,pk),c=fac(n-m,p,pk);
	Int64 cnt=0;
	for(Int64 i=n;i;i/=p)cnt+=i/p;
	for(Int64 i=m;i;i/=p)cnt-=i/p;
	for(Int64 i=n-m;i;i/=p)cnt-=i/p;
	return a*powm(b*c%pk,pk/p*(p-1)-1,pk)*powm(p,cnt,pk)%pk;
}
int main(){
	Int64 n,m;
	int p;
	scanf("%lld%lld%d",&n,&m,&p);
	int x=p;
	Int64 res=0;
	for(int i=2;i<=x;++i)
		if(x%i==0){
			int cnt=0,pow=1;
			do ++cnt,x/=i,pow*=i;
			while(x%i==0);
			Int64 val=lucas(n,m,i,pow);
			Int64 k=(p/pow)*powm(p/pow,pow/i*(i-1)-1,pow);
			res=(res+val*k)%p;
		}
	printf("%lld\n",res);
	return 0;
}

