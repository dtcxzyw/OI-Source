#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
typedef long long Int64;
const Int64 size=1000100,mod=666623333;
Int64 siz,bsiz,sum[size],prime[size];
bool flag[size]={};
void pre(){
    bsiz=std::min(siz,1000000LL);
    sum[1]=1;
    Int64 pcnt=0;
    for(Int64 i=2;i<=bsiz;++i){
        if(!flag[i])prime[++pcnt]=i,sum[i]=i-1;
        for(Int64 j=1;j<=pcnt && prime[j]*i<=bsiz;++j){
            Int64 val=i*prime[j];
            flag[val]=true;
            if(i%prime[j])sum[val]=sum[i]*(prime[j]-1)%mod;
            else{
                sum[val]=sum[i]*prime[j]%mod;
                break;
            }
        }
    }
    for(Int64 i=1;i<=bsiz;++i)sum[i]=(sum[i]+sum[i-1])%mod;
}
Int64 powm(Int64 a,Int64 k){
    Int64 res=1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1,a=a*a%mod;
    }
    return res;
}
Int64 inv2,lc[size],hc[size];
Int64& get(Int64 x){
	if(x<=bsiz)lc[x];
	return hc[siz/x];
}
//f(n)=sigma(n,phi(i))=sigma(n,i)-sigma(2,n,f(n/i))
Int64 f(Int64 x){
    if(x<=bsiz)return sum[x];
    Int64& res=get(x);
    if(res>=0)return res;
    res=(x%mod)*((1+x)%mod)%mod*inv2%mod;
    Int64 end;
    for(Int64 i=2;i<=x;i=end+1){
        Int64 div=x/i;
        end=x/div;
        res=(res-(end-i+1)%mod*f(div)%mod)%mod;
    }
    res=(res+mod)%mod;
    return res;
}
int main(){
    inv2=powm(2,mod-2);
    Int64 l,r;
    scanf("%lld%lld",&l,&r);
    siz=r;
    pre();
    memset(lc,0xc0,sizeof(lc));
    memset(hc,0xc0,sizeof(hc));
    Int64 b=f(r);
    memset(lc,0xc0,sizeof(lc));
    memset(hc,0xc0,sizeof(hc));
    Int64 e=f(l-1);
    Int64 delta=(b-e+mod)%mod;
    Int64 sum=(l+r)%mod*(r-l+1)%mod*inv2%mod;
    Int64 ans=(sum-delta+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}

