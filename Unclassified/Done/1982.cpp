#include <cstdio>
#include <algorithm>
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
long long K[1000000];
int main(){
    int n,p;
    n=read();
    p=read();
    long long sum=std::max(K[0]=read(),0LL);
    
    for(int i=1;i<n;++i){
        sum+=read();
        K[i]=std::max(K[i-1],sum);
        if(sum<0)sum=0;
    }
    long long maxv=K[0]<<1,ans=K[0];
    for(int i=1;i<n;++i){
        if(maxv>=0)ans=maxv;
        else ans=std::max(ans,maxv);
        if(K[i]>0){
            maxv+=K[i];
            if(maxv>0)maxv%=p;
        }
    }
    
    printf("%lld\n",ans%p);
    return 0;
}

