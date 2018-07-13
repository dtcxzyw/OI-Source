#include <cstdio>
typedef long long ll;
ll powm(ll a,ll k,ll m){
    ll res=1;
    while(k){
        if(k&1)res=res*a%m;
        k>>=1,a=a*a%m;
    }
    return res;
}
void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(b){
        exgcd(b,a%b,d,y,x);
        y-=a/b*x;
    }
    else d=a,x=1,y=0;
}
int main(){
    ll n,m,l;
    scanf("%lld%lld%lld",&n,&m,&l);
    ++n;
    ll a=powm(2,m,n),d,x,y;
    exgcd(a,n,d,x,y);
    printf("%lld\n",((x*l/d)%n+n)%n);
    return 0;
}

