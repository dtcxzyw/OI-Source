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
const int size=300005,mod=998244353,g=3;
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
int A[size]={},B[size]={},C[size]={},invP[100005];
int main(){
    int n=read();
    int m=1;
    while(m<(n<<1))m<<=1;
    init(m);
    for(int i=0;i<n;++i)A[i]=read();
    inv(n,A,B,C);
    for(int i=0;i<n;++i)A[i]=asInt64(A[i+1])*(i+1)%mod;
    NTT(m,A,root);
    NTT(m,B,root);
    for(int i=0;i<m;++i)
    	A[i]=asInt64(A[i])*B[i]%mod;
    NTT(m,A,invR);
    Int64 invM=powm(m,mod-2);
    invP[1]=1;
    for(int i=2;i<n;++i)
    	invP[i]=asInt64(mod-mod/i)*invP[mod%i]%mod;
    for(int i=n-1;i>=1;--i)
    	A[i]=A[i-1]*invM%mod*invP[i]%mod;
    A[0]=0;
    for(int i=0;i<n;++i)
    	printf("%d ",A[i]);
    return 0;
}

