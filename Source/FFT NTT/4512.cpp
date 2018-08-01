#include <cstdio>
#include <algorithm>
#include <cstring>
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
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size=600005,mod=998244353,g=3;
Int64 powm(Int64 a,int k){
    Int64 res=1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1,a=a*a%mod;
    }
    return res;
}
int add(int a,int b){
    a+=b;
    return a>=mod?a-mod:a;
}
int sub(int a,int b){
    a-=b;
    return a<0?a+mod:a;
}
int root[size],invR[size],tot;
void init(int n){
    tot=n;
    Int64 base=powm(g,(mod-1)/n);
    Int64 invBase=powm(base,mod-2);
    root[0]=invR[0]=1;
    for(int i=1;i<n;++i)root[i]=root[i-1]*base%mod;
    for(int i=1;i<n;++i)invR[i]=invR[i-1]*invBase%mod;
}
void NTT(int n,int* A,int* w){
    for(int i=0,j=0;i<n;++i){
        if(i>j)std::swap(A[i],A[j]);
        for(int l=n>>1;(j^=l)<l;l>>=1);
    }
    for(int i=2;i<=n;i<<=1){
        int m=i>>1,fac=tot/i;
        for(int j=0;j<n;j+=i){
            for(int k=0;k<m;++k){
                int t=asInt64(A[j+k+m])*w[fac*k]%mod;
                A[j+k+m]=sub(A[j+k],t);
                A[j+k]=add(A[j+k],t);
            }
        }
    }
}
void inv(int n,int* A,int* B,int* tmp){
    if(n==1)B[0]=powm(A[0],mod-2);
    else{
        inv((n+1)>>1,A,B,tmp);
        int p=1;
        while(p<(n<<1))p<<=1;
        memcpy(tmp,A,sizeof(int)*n);
        memset(tmp+n,0,sizeof(int)*(p-n));
        NTT(p,tmp,root);
        NTT(p,B,root);
        for(int i=0;i<p;++i){
            B[i]=(2-asInt64(tmp[i])*B[i]%mod)*B[i]%mod;	
            if(B[i]<0)B[i]+=mod;
        }
        NTT(p,B,invR);
        Int64 div=powm(p,mod-2);
        for(int i=0;i<n;++i)
            B[i]=B[i]*div%mod;
        memset(B+n,0,sizeof(int)*(p-n));
    }
}
int T1[size],T2[size];
void mul(int n,int* A,int* B,int* C){
    memcpy(T1,A,sizeof(int)*n);
    memcpy(T2,B,sizeof(int)*n);
    A=T1,B=T2;
    NTT(n,A,root);
    NTT(n,B,root);
    for(int i=0;i<n;++i)
        C[i]=asInt64(A[i])*B[i]%mod;
    NTT(n,C,invR);
    Int64 div=powm(n,mod-2);
    for(int i=0;i<n;++i)
        C[i]=C[i]*div%mod;
}
int A[size]={},B[size]={},C[size]={},D[size]={};
int main(){
    int n=read();
    int m=read();
    int k=1;
    while(k<((n+1)<<1))k<<=1;
    init(k);
    for(int i=0;i<=n;++i)A[n-i]=read();
    for(int i=0;i<=m;++i)B[m-i]=read();
    inv(n-m+1,B,C,T1);
    mul(k,A,C,D);
    memset(D+n-m+1,0,sizeof(int)*(k-(n-m+1)));
    std::reverse(A,A+n+1);
    std::reverse(B,B+m+1);
    std::reverse(D,D+n-m+1);
    mul(k,D,B,C);
    int ddeg=n-m;
    for(int i=0;i<=ddeg;++i)
        printf("%d ",D[i]);
    puts("");
    for(int i=0;i<m;++i)
        printf("%d ",sub(A[i],C[i]));
    return 0;
}

