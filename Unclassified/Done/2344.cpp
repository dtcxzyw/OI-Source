#include <cstdio>
#include <algorithm>
#include <cstring>
const int mod=1000000009,size=100010;
int s[size],sc[size];
int read(){
    int res=0,c;
    bool flag=false;
    do{ 
        c=getchar();
        flag|=c=='-';
    }while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return flag?-res:res;
}
int A[size]={},siz;
void add(int i,int v){
    while(i<=siz){
        A[i]=(A[i]+v)%mod;
        i+=i&-i;
    }
}
int query(int i){
    int ans=0;
    while(i>0){
        ans=(ans+A[i])%mod;
        i-=i&-i;
    }
    return ans;
}
int main(){
    int n=read();
    s[0]=sc[0]=0;
    for(int i=1;i<=n;++i)sc[i]=s[i]=s[i-1]+read();
    std::sort(sc,sc+n+1);
    siz=std::unique(sc,sc+n+1)-sc;
    add(std::lower_bound(sc,sc+siz,0)-sc+1,1);
    int ans;
    for(int i=1;i<=n;++i){
        int p=std::lower_bound(sc,sc+siz,s[i])-sc+1;
        ans=query(p);
        add(p,ans);
    }
    printf("%d\n",ans);
    return 0;
}

