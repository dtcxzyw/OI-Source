#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
typedef long long Int64;
const Int64 size=100100,psiz=1000100;
Int64 bsiz,prime[psiz/10],mu[size],fac[size],pcnt=0;
bool flag[psiz]={};
void pre(Int64 siz){
    bsiz=std::min(psiz-1,static_cast<Int64>(sqrt(siz)));
    for(Int64 i=2;i<=bsiz;++i){
        if(!flag[i])prime[++pcnt]=i;
        for(Int64 j=1;j<=pcnt && prime[j]*i<=bsiz;++j){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0)break;
        }
    }
}
typedef __int128 Int128;
Int64 powm(Int128 a,Int64 k,Int128 mod){
	Int128 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
bool isPrime(Int64 x){
	return powm(2,x-1,x)==1 && powm(3,x-1,x)==1;
}
int main(){
    Int64 l,r;
    scanf("%lld%lld",&l,&r);
    pre(r);
    Int64 len=r-l;
    for(int i=0;i<=len;++i)
    	mu[i]=1,fac[i]=i+l;
    for(int i=1;i<=pcnt;++i){
    	Int64 x=l/prime[i]*prime[i];
    	if(x==l)x-=prime[i];
    	while((x+=prime[i])<=r){
    		fac[x-l]/=prime[i];
    		mu[x-l]=-mu[x-l];
    		while(fac[x-l]%prime[i]==0)
    			fac[x-l]/=prime[i],mu[x-l]=0;
    	}
    }
    for(int i=0;i<=len;++i)
    	if(fac[i]!=1){
    		Int64 sq=sqrt(fac[i]);
    		if(sq*sq==fac[i])mu[i]=0;
    		else if(isPrime(fac[i]))mu[i]=-mu[i];
    	}
    Int64 ans=0;
    for(int i=0;i<=len;++i)
        ans+=mu[i];
    printf("%lld\n",ans);
    return 0;
}

