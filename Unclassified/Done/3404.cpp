#include <cstdio>
#include <algorithm>
using namespace std;
const int mod=1000000009,size=100001<<2|1;
inline int subm(int a,int b){
    return ((a-b)%mod+mod)%mod;
}
struct Mat2{
    int data[2][2]={};
    Mat2 operator*(const Mat2& rhs) const{
        Mat2 res;
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                for(int k=0;k<2;++k)
                    res.data[i][j]=(res.data[i][j]+1LL*data[i][k]*rhs.data[k][j]%mod)%mod;
        return res;
    }
};
int fib(int a,int b,int k){
    Mat2 res,base;
    res.data[0][0]=subm(b,a),res.data[0][1]=res.data[1][0]=a,res.data[1][1]=b;
    base.data[0][1]=base.data[1][0]=base.data[1][1]=1;
    --k;
    while(k){
        if(k&1)res=res*base;
        k>>=1,base=base*base;
    }
    return res.data[0][1];
}

inline int fibSum(int a,int b,int n){
    return subm((fib(a,b,n+1)+fib(a,b,n))%mod,b);
}

int sum[size],lazy1[size]={},lazy2[size]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1

void color(int l,int r,int id,int f1,int f2){
    if(l==r)sum[id]=(sum[id]+f1)%mod;
    else{
        lazy1[id]=(lazy1[id]+f1)%mod,lazy2[id]=(lazy2[id]+f2)%mod;
        sum[id]=(sum[id]+fibSum(f1,f2,r-l+1))%mod;
    }
}

inline void update(int id){
    sum[id]=(sum[id<<1]+sum[id<<1|1])%mod;
}

void push(int l,int r,int id){
    if(lazy1[id] || lazy2[id]){
        int m=(l+r)>>1;
        color(ls,lazy1[id],lazy2[id]);
        color(rs,fib(lazy1[id],lazy2[id],m+2-l),fib(lazy1[id],lazy2[id],m+3-l));
        lazy1[id]=lazy2[id]=0;
    }
}

void modify(int l,int r,int id,int nl,int nr){
    if(nl<=l && r<=nr){
        int pos=l-nl;
        color(l,r,id,fib(1,1,pos+1),fib(1,1,pos+2));
    }
    else{
        push(l,r,id);
        int m=(l+r)>>1;
        if(nl<=m)modify(ls,nl,nr);
        if(m<nr)modify(rs,nl,nr);
        update(id);
    }
}

int query(int l,int r,int id,int nl,int nr){
    if(nl<=l && r<=nr)return sum[id];
    else{
        int ans=0,m=(l+r)>>1;
        push(l,r,id);
        if(nl<=m)ans=query(ls,nl,nr);
        if(m<nr)ans=(ans+query(rs,nl,nr))%mod;
        return ans;
    }
}

int read(){
    int res=0,c;
    do c=getchar();
    while(c<'0' || c>'9');
    while('0'<=c && c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return res;
}

void build(int l,int r,int id){
    if(l==r)sum[id]=read();
    else{
        int m=(l+r)>>1;
        build(ls);
        build(rs);
        update(id);
    }
}

int main(){
    int n,m;
    n=read();
    m=read();
    build(1,n,1);
    int c,l,r;
    for(int i=0;i<m;++i){
        c=read();
        l=read();
        r=read();
        if(c==1)modify(1,n,1,l,r);
        else printf("%d\n",query(1,n,1,l,r));
    }
    return 0;
}

