#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
long long powm(long long a,long long k,long long p){
    long long res=1;
    while(k){
        if(k&1)res=res*a%p;
        k>>=1,a=a*a%p;
    }
    return res;
}
const int size=1<<16;
typedef std::vector<std::pair<int,int> > Vec;
Vec LUT[size]={};
long long calcK(long long g,long long mod,int block,int x){
    long long val=x;
    for(int i=1;i<=block;++i){
        val=val*g%mod;
        Vec& ref=LUT[val>>16];
        for(int j=0;j<ref.size();++j)
            if(ref[j].first==val)
                return ref[j].second*block-i;
    }
    return -1;
}
int main(){
    int g,p,n;
    scanf("%d%d%d",&g,&p,&n);
    int block=sqrt(p)+1;
    {
        long long gb=powm(g,block,p),powv=1;
        for(int i=1;i<=block;++i){
            powv=powv*gb%p;
            LUT[powv>>16].push_back(std::make_pair<int,int>(powv,i));
        }
    }
    for(int i=0;i<n;++i){
        int A,B;
        scanf("%d%d",&A,&B);
        long long a=calcK(g,p,block,A);
        long long b=calcK(g,p,block,B);
        printf("%lld\n",powm(g,a*b,p));
    }
    return 0;
}

