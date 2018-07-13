#include <cstdio>
typedef long long Int64;
const int mod=19940417;
void exgcd(int a,int b,int& x,int& y){
    if(b){
        exgcd(b,a%b,y,x);
        y-=a/b*x;
    }
    else x=1,y=0;
}
Int64 inv(int x){
    int a,b;
    exgcd(x,mod,a,b);
    return (a+mod)%mod;
}
Int64 inv6;
Int64 sum1(Int64 n){
    return ((n*(n+1))>>1)%mod;
}
Int64 sum1(Int64 b,Int64 e){
    return sum1(e)-sum1(b-1);
}
Int64 sum2(Int64 n){
    return n*(n+1)%mod*(n<<1|1)%mod*inv6%mod;
}
Int64 sum2(Int64 b,Int64 e){
    return sum2(e)-sum2(b-1);
}
#define asInt64(x) static_cast<Int64>(x)
Int64 query1(int n){
    Int64 res=asInt64(n)*n%mod;
    for(int i=1;i<=n;++i){
        int div=n/i,j=n/div;
        res=(res-sum1(i,j)*div)%mod;
        i=j;
    }
    return res;
}
int minv(int a,int b){
    return a<b?a:b;
}
Int64 query2(int n,int m){
    int end=minv(n,m);
    Int64 res=asInt64(n)*m%mod*end%mod;
    for(int i=1;i<=end;++i){
        int div1=n/i;
        int div2=m/i;
        int j=minv(n/div1,m/div2);
        Int64 sum=sum1(i,j);
        res=(res-sum*div1%mod*m)%mod;
        res=(res-sum*div2%mod*n)%mod;
        res=(res+sum2(i,j)*div1%mod*div2)%mod;
        i=j;
    }
    return res;
}
int main(){
    inv6=inv(6);
    int n,m;
    scanf("%d%d",&n,&m);
    Int64 l=query1(n);
    Int64 r=query1(m);
    Int64 sub=query2(n,m);
    int ans=((l*r-sub)%mod+mod)%mod;
    printf("%d\n",ans);
    return 0;
}

