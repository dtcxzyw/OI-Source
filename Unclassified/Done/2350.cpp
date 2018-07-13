#include <cstdio>
#include <cstring>
const int size=10005;
int prime[size],f[size*10]={};
bool flag[size*10]={};
void pre(int n){
    int pcnt=0;
    f[1]=1;
    for(int i=2;i<=n;++i){
        if(!flag[i]){
            ++pcnt;
            prime[pcnt]=i;
            f[i]=f[i-1];
        }
        for(int j=1;j<=pcnt && prime[j]*i<=n;++j){
            int val=prime[j]*i;
            flag[val]=true;
            f[val]=f[prime[j]]+f[i];
            if(i%prime[j]==0)break;
        }
    }
}
long long foo(){
    int m;
    scanf("%d",&m);
    long long res=1;
    for(int i=0;i<m;++i){
        int p,q;
        scanf("%d%d",&p,&q);
        res+=static_cast<long long>(f[p])*q-(p==2);
    }
    return res;
}
int main(){
    pre(100000);
    int t;
    scanf("%d",&t);
    while(t--)printf("%lld\n",foo());
    return 0;
}

