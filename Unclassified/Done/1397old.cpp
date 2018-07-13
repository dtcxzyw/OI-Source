#include <cstdio>
typedef long long Int64;
const Int64 mod=1000000007LL,phi=mod-1,invk=mod-2;
Int64 read(Int64 mv=mod){
    Int64 res=0;
    int c;
    do c=getchar();
    while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=(res*10+c-'0')%mv;
        c=getchar();
    }
    return res;
}
Int64 powm(Int64 a,Int64 k){
    Int64 res=1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1,a=a*a%mod;
    }
    return res;
}
Int64 inv(Int64 a){
    return powm(a,invk);
}
Int64 clamp(Int64 x){
    return (x%mod+mod)%mod;
}
Int64 sum(Int64 a,Int64 k){
    if(a==1)return clamp(k+1);
    return clamp(powm(a,k+1)-1)*inv(a-1)%mod;
}
Int64 calc(Int64 x,Int64 a,Int64 b,Int64 k){
    Int64 l=powm(a,k-1)*x%mod;
    Int64 r=b*sum(a,k-2)%mod;
    return (l+r)%mod;
}
int main(){
    Int64 n=read(phi);
    Int64 m=read(phi);
    Int64 a=read();
    Int64 b=read();
    Int64 c=read();
    Int64 d=read();
    Int64 v1m=calc(1,a,b,m);
    Int64 pv=powm(a,m-1);
    Int64 A=pv*c%mod;
    Int64 B=(pv*d%mod+b*sum(a,m-2)%mod)%mod;
    printf("%lld\n",calc(v1m,A,B,n));
    return 0;
}

