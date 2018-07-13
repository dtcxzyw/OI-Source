#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int size=20005;
void modify(int* A,int siz,int x,int op){
    while(x<=siz){
        A[x]+=op;
        x+=x&-x;
    }
}
int query(int* A,int x){
    int res=0;
    while(x){
        res+=A[x];
        x-=x&-x;
    }
    return res;
}
int h[size],tmp[size],S[size]={},SB[150][size]={},bid[size],n,bsiz,siz,cur=0;
void modifyBlock(int bid,int id,int op,int dir){
    modify(SB[bid],siz,h[id],op);
    int begin=std::max(1,bsiz*bid),end=std::min(n+1,bsiz*(bid+1));
    if(dir==0){
        for(int i=begin;i<id;++i)
            if(h[i]>h[id])cur+=op;
            else if(h[i]<h[id])cur-=op;
    }
    else {
        for(int i=id+1;i<end;++i)
            if(h[id]>h[i])cur+=op;
            else if(h[id]<h[i])cur-=op;
    }
}
int main(){
    n=read();
    for(int i=1;i<=n;++i)
        h[i]=read();
    memcpy(tmp,h,sizeof(tmp));
    std::sort(tmp+1,tmp+n+1);
    siz=std::unique(tmp+1,tmp+n+1)-(tmp+1);
    for(int i=1;i<=n;++i)
        h[i]=std::lower_bound(tmp+1,tmp+siz+1,h[i])-tmp;
    for(int i=1;i<=n;++i){
        modify(S,siz,h[i],1);
        cur+=i-query(S,h[i]);
    }
    printf("%d\n",cur);
    bsiz=sqrt(n);///log2(n+1);
    if(bsiz<=0)bsiz=1;
    for(int i=1;i<=n;++i){
        int id=i/bsiz;
        bid[i]=id;
        modify(SB[id],siz,h[i],1);
    }
    int m=read();
    for(int i=1;i<=m;++i){
        int a=read();
        int b=read();
        if(a>b)std::swap(a,b);
        int ai=bid[a],bi=bid[b];
        if(ai==bi){
            for(int j=a+1;j<b;++j){
                if(h[j]<h[a])--cur;
                if(h[j]>h[a])++cur;
                if(h[j]<h[b])++cur;
                if(h[j]>h[b])--cur;
            }
        }
        else{
            modifyBlock(ai,a,-1,1);
            modifyBlock(bi,b,-1,0);
            for(int j=ai+1;j<bi;++j){
                cur-=query(SB[j],h[a])+query(SB[j],h[a]-1);
                cur+=query(SB[j],h[b]-1)+query(SB[j],h[b]);
            }
        }
        if(h[a]>h[b])--cur;
        else if(h[a]<h[b])++cur;
        std::swap(h[a],h[b]);
        if(ai!=bi){
            modifyBlock(ai,a,1,1);
            modifyBlock(bi,b,1,0);
        }
        printf("%d\n",cur);
    }
    return 0;
}

