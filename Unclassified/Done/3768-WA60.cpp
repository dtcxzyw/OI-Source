#include <cstdio>
const int size=30000100;
typedef long long Int64;
Int64 f[size];
Int64 powm(Int64 a,Int64 k,Int64 p){
    Int64 res=1;
    while(k){
        if(k&1)res=res*a%p;
        k>>=1,a=a*a%p;
    }
    return res;
}
int main(){
	Int64 p,n;
	scanf("%lld%lld",&p,&n);
	Int64 ans=0,inv2=powm(2,p-2,p);
	for(Int64 i=n;i>=1;--i){
		Int64 x=(n/i)%p;
		Int64 sum=x*(x+1)%p*inv2%p*i%p;
		f[i]=sum*sum%p;
		for(Int64 j=i<<1;j<=n;j+=i)
			f[i]=(f[i]-f[j])%p;
		ans=(ans+f[i]*i%p)%p;
	}
	ans=(ans+p)%p;
	printf("%lld\n",ans); 
	return 0;
}

