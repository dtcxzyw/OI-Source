#include <cstdio>
#include <cmath>
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
inline long long asInt64(int x){
    return x;
}
const int size=50010,lsiz=40,block=1<<14;
int num[size],sum[size<<2],cnt[size],p,phi[lsiz],maxd,c,powL[lsiz][block],powH[lsiz][block];
double lgc,lgp[lsiz];
int powm(int k,int mod){
    return asInt64(powH[mod][k>>14])*powL[mod][k&(block-1)]%phi[mod];
}
bool test(int i,int j,int modi){
    if(j==0)return i<phi[modi];
    while(j--){
        if(i*lgc>=lgp[modi])return false;
        i=powm(i,modi);
    }
    return true;
}
int calc(int i,int j,int modi){
    if(modi==maxd)return 0;
    if(j==0)return i%phi[modi];
    bool res=test(i,j-1,modi+1);
    if(res)return powm(calc(i,j-1,modi+1),modi);
    return powm(calc(i,j-1,modi+1)+phi[modi+1],modi);
}
bool mask[size<<2];
int euler(int x){
    int res=x;
    for(int i=2;i*i<=x && x!=1;++i)
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0)x/=i;
        }
    if(x>1)res=res/x*(x-1);
    return res;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int id){
    sum[id]=(sum[id<<1]+sum[id<<1|1])%p;
    mask[id]=(mask[id<<1]|mask[id<<1|1]);
}
void build(int l,int r,int id){
    if(l==r)
        sum[id]=num[l],mask[id]=(0!=maxd),cnt[l]=0;
    else{
        int m=(l+r)>>1;
        build(ls);
        build(rs);
        update(id);
    }
}
int nl,nr;
void modify(int l,int r,int id){
    if(mask[id]){
        if(l==r){
        	sum[id]=calc(num[l],++cnt[l],0);
        	if(cnt[l]>maxd)mask[id]=false;
        }else{
            int m=(l+r)>>1;
            if(nl<=m)modify(ls);
            if(m<nr)modify(rs);
            update(id);
        }
    }
}
int query(int l,int r,int id){
    if(nl<=l && r<=nr)return sum[id];
    else{
        int m=(l+r)>>1,res=0;
        if(nl<=m)res+=query(ls);
        if(m<nr)res+=query(rs);
        return res%p;
    }
}
int main(){
    int n=read();
    int m=read();
    phi[0]=p=read();
    for(maxd=0;phi[maxd]!=1;++maxd)
        phi[maxd+1]=euler(phi[maxd]);

    c=read();
    lgc=log(c);
    for(int i=0;i<=maxd;++i){
        lgp[i]=log(phi[i]);
        powL[i][0]=powH[i][0]=1;
        for(int j=1;j<block;++j)powL[i][j]=asInt64(powL[i][j-1])*c%phi[i];
        long long mul=asInt64(powL[i][block-1])*c%phi[i];
        for(int j=1;j<block;++j)powH[i][j]=asInt64(powH[i][j-1])*mul%phi[i];
    }

    for(int i=1;i<=n;++i)
        num[i]=read();

    build(1,n,1);
    int op;
    for(int i=0;i<m;++i){
        op=read();
        nl=read();
        nr=read();
        if(op)printf("%d\n",query(1,n,1));
        else modify(1,n,1);
    }
    return 0;
}

