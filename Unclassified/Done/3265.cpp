#include <cstdio>
#include <algorithm>
int read(){
    int res=0,c;
    do c=getchar();
    while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return res;
}
const int size=505,mod=1000000007;
long long inv(long long x){
    long long res=1;
    int k=mod-2;
    while(k){
        if(k&1)res=res*x%mod;
        k>>=1,x=x*x%mod;
    }
    return res;
}
struct Vec{
    int k[size],val;
    bool operator<(const Vec& rhs) const{
        return val<rhs.val;
    }	
} A[size];
int bit[size]={},cnt=0,sum=0;
int main(){
    int n=read();
    int m=read();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            A[i].k[j]=read();
    for(int i=1;i<=n;++i)
        A[i].val=read();
    std::sort(A+1,A+n+1);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j)
            if(A[i].k[j]){
                int& x=bit[j];
                if(x){
                    long long mul=A[i].k[j]*inv(A[x].k[j])%mod;
                    for(int k=j;k<=m;++k)
                        A[i].k[k]=(A[i].k[k]-A[x].k[k]*mul)%mod;
                }
                else{
                    x=i,++cnt,sum+=A[i].val;
                    break;
                }
            }
    }
    if(cnt==0)printf("1 %d\n",A[1].val);
    else printf("%d %d\n",cnt,sum);
    return 0;
}


