#include <cstdio>
#include <cstring>
#include <set>
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
const int size=100001,mod=1000000007;
long long inv[10001],fac[size];
void pre(int n){
    inv[0]=inv[1]=1;
    for(int i=2;i<=10000;++i)
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    fac[n]=1,fac[n-1]=2;
    for(int i=n-2;i>=1;--i)
        fac[i]=(fac[i+1]*3)%mod;
}
int A[size];
long long S[size],sum[size<<2],lazy[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
    lazy[id]=1;
    if(l==r)sum[id]=fac[l]*S[l]%mod;
    else{
        int m=(l+r)>>1;
        build(ls);
        build(rs);
        sum[id]=(sum[id<<1]+sum[id<<1|1])%mod;
    }
}
void color(int id,long long val){
    sum[id]=sum[id]*val%mod;
    lazy[id]=lazy[id]*val%mod;
}
void push(int id){
    if(lazy[id]!=1){
        color(id<<1,lazy[id]);
        color(id<<1|1,lazy[id]);
        lazy[id]=1;	
    }
}
int beg;
long long val;
void modify(int l,int r,int id){
    if(beg<=l)color(id,val);
    else{
        push(id);
        int m=(l+r)>>1;
        if(beg<=m)modify(ls);
        modify(rs);
        sum[id]=(sum[id<<1]+sum[id<<1|1])%mod;
    }
}
int end;
long long res;
void query(int l,int r,int id){
    if(r<=end)res=(res+sum[id])%mod;
    else{
        push(id);
        int m=(l+r)>>1;
        query(ls);
        if(m<end)query(rs);
    }
}
std::set<int> zero;
int main(){
    int n=read();
    int q=read();
    for(int i=1;i<=n;++i)A[i]=read();
    
    pre(n);
    S[0]=1;
    zero.insert(n+1);
    for(int i=1;i<=n;++i)
        if(A[i])S[i]=S[i-1]*A[i]%mod;
        else S[i]=S[i-1],zero.insert(i);
    build(1,n,1);
    
    for(int i=0;i<q;++i){
        int u=read();
        int old=A[u];
        A[u]=read();
        val=inv[old]*std::max(A[u],1)%mod;
        beg=u;
        if(val!=1)modify(1,n,1);
        if(old!=0 && A[u]==0)zero.insert(u);
        else if(old==0 && A[u]!=0)zero.erase(u);
        end=*zero.begin()-1;
        res=0;
        if(end)query(1,n,1);
        printf("%d\n",static_cast<int>(res));
    }
    return 0;
}

