#include <cstdio>
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
void printImpl(int x){
    if(x>=10)printImpl(x/10);
    putchar('0'+x%10);
}
void print(int x){
    printImpl(x);
    putchar('\n');
}
const int mod=998244353;
int inv(int a){
    int k=mod-2,res=1;
    while(k){
        if(k&1)res=1LL*res*a%mod;
        k>>=1,a=1LL*a*a%mod;
    }
    return res;
}
const int size=100100;
struct Seg{
    int ls,rs,val;
} seg[size*200];
int cnt=0,root[size*200],n,ans;
#define ls l,m,seg[id].ls
#define rs m+1,r,seg[id].rs 
int merge(int x,int y){
    return (1LL*x*y%mod+1LL*(1-x+mod)*(1-y+mod)%mod)%mod;
}
void modifyR(int l,int r,int& id,int nl,int nr,int x){
    if(!id){
        id=++cnt;
        seg[id].val=1;
    }
    if(nl<=l && r<=nr)seg[id].val=merge(seg[id].val,x);
    else{
        int m=(l+r)>>1;
        if(nl<=m)modifyR(ls,nl,nr,x);
        if(m<nr)modifyR(rs,nl,nr,x);
    }
}
bool test(int l1,int r1,int l2,int r2){
    return r1>=l2 && r2>=l1;
}
void modifyL(int l,int r,int& id,int nl,int nr,int ml,int mr,int x){
    if(!id)id=++cnt;
    if(nl<=l && r<=nr){
        if(l+1<=n && test(l+1,n,ml,mr))
            modifyR(l+1,n,root[id],ml,mr,x);
    }
    else{
        int m=(l+r)>>1;
        if(nl<=m)modifyL(ls,nl,nr,ml,mr,x);
        if(m<nr)modifyL(rs,nl,nr,ml,mr,x);
    }
}
void queryR(int l,int r,int id,int p){
    if(id){
        ans=merge(ans,seg[id].val);
        if(l!=r){
            int m=(l+r)>>1;
            if(p<=m)queryR(ls,p);
            else queryR(rs,p);
        }	
    }
}
void queryL(int l,int r,int id,int p1,int p2){
    if(id){
        if(l+1<=p2)queryR(l+1,n,root[id],p2);
        if(l!=r){
            int m=(l+r)>>1;
            if(p1<=m)queryL(ls,p1,p2);
            else queryL(rs,p1,p2);
        }
    }
}
int main(){
    n=read();
    int m=read();
    int R=0;
    for(int i=1;i<=m;++i){
        int op=read();
        int l=read();
        int r=read();
        if(op==1){
            int x=inv(r-l+1),y=(1-x+mod)%mod,z=(1-x*2%mod+mod)%mod;
            //left
            if(l>1){
                modifyL(1,n,R,1,l-1,l,r,y);
                modifyR(1,n,root[0],1,l-1,0);
            }
            //mid
            if(l!=r)modifyL(1,n,R,l,r,l,r,z);
            modifyR(1,n,root[0],l,r,x);
            //right
            if(r<n){
                modifyL(1,n,R,l,r,r+1,n,y);
                modifyR(1,n,root[0],r+1,n,0);
            }
        }
        else{
            ans=1;
            if(l==1)queryR(1,n,root[0],r);
            else queryL(1,n,R,l-1,r);
            print(ans);
        }
    }
    return 0;
}

