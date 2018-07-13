#include <cstdio>
typedef long long Int64;
Int64 powm(Int64 a,Int64 k,Int64 p){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%p;
		k>>=1,a=a*a%p;
	}
	return res;
}
int main(){
	Int64 m,n,k,p;
	scanf("%lld%lld%lld%lld",&n,&k,&m,&p);
	Int64 sum=powm(m,k-2,p);
	Int64 cnt=(k-1)*sum%p;
	Int64 seq=((m+1)*m/2)%p;
	Int64 sub=cnt*seq%p;
	n%=p;
	Int64 ans=(sum*m%p*n%p-sub+p)%p;
	printf("%lld\n",ans);
	return 0;
}

