#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
typedef long long Int64;
const Int64 size=1000100,mod=666623333;
Int64 bsiz,prime[size],phi[size],fac[size],pcnt=0;
bool flag[size]={};
void pre(Int64 siz){
    bsiz=sqrt(siz);
    for(Int64 i=2;i<=bsiz;++i){
        if(!flag[i])prime[++pcnt]=i;
        for(Int64 j=1;j<=pcnt && prime[j]*i<=bsiz;++j){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0)break;
        }
    }
}
int main(){
    Int64 l,r;
    scanf("%lld%lld",&l,&r);
    pre(r);
    Int64 len=r-l;
    for(int i=0;i<=len;++i)
    	phi[i]=fac[i]=i+l;
    for(int i=1;i<=pcnt;++i){
    	Int64 x=l/prime[i]*prime[i];
    	if(x==l)x-=prime[i];
    	while((x+=prime[i])<=r){
    		phi[x-l]=phi[x-l]/prime[i]*(prime[i]-1);
    		do fac[x-l]/=prime[i];
    		while(fac[x-l]%prime[i]==0);
    	}
    }
    for(int i=0;i<=len;++i)
    	if(fac[i]!=1)
    		phi[i]=phi[i]/fac[i]*(fac[i]-1);
    Int64 ans=0;
	for(int i=0;i<=len;++i)
		ans=(ans+i+l-phi[i])%mod;
    printf("%lld\n",ans);
    return 0;
}

