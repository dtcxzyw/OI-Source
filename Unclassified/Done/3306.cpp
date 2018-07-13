#include <cstdio>
#include <map>
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
int powm(int a,int k,int p){
    int res=1;
    while(k){
        if(k&1)res=1LL*res*a%p;
        k>>=1,a=1LL*a*a%p;
    }
    return res;
}
int inv(int a,int p){
    return powm(a,p-2,p);
}
int bsgs(int a,int b,int p){
    if(a%p==0)return -1;
    int m=ceil(sqrt(p));
    std::map<int,int> table;
    int now=b%p;
    for(int j=0;j<=m;++j){
        table[now]=j;
        now=1LL*now*a%p;
    }
    int base=powm(a,m,p);
    now=1;
    for(int i=1;i<=m;++i){
        now=1LL*now*base%p;
        std::map<int,int>::iterator it=table.find(now);
        if(it!=table.end())
            return i*m-it->second+1;
    }
    return -1;
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
void foo(){
    int p=read();
    int a=read();
    int b=read();
    int x1=read();
    int t=read();
    if(x1==t)puts("1");
    else if(a==0)puts(b==t?"2":"-1");
    else if(a==1){
        int r=((t-x1)%p+p)%p;
        if(r%gcd(b,p))puts("-1");
        else printf("%d\n",1LL*r*inv(b,p)%p+1);
    }
    else{
        int fac1=1LL*b*inv(a-1,p)%p;
        int r=(t+fac1)%p;
        int l=(x1+fac1)%p;
        int fac2=1LL*r*inv(l,p)%p;
        printf("%d\n",bsgs(a,fac2,p));
    }
}
int main(){
    int t=read();
    for(int i=0;i<t;++i)foo();
    return 0;
}

