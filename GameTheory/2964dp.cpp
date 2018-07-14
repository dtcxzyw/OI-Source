#include <cstdio>
#include <algorithm>
const int size=2005;
int n,c[size],dp[size][size];
int main(){
    scanf("%d",&n);
    for(int i=n;i>=1;--i)
        scanf("%d",&c[i]);
    for(int i=1;i<=n;++i)
        c[i]+=c[i-1];
    for(int i=1;i<=n;++i){
        int res=1<<30;
        for(int j=1;j<=n;++j){
            int k1=j<<1;
            if(i>=k1)res=std::min(res,dp[i-k1][k1]);
            int k2=k1-1;
            if(i>=k2)res=std::min(res,dp[i-k2][k2]);
            dp[i][j]=c[i]-res;
        }
    }
    printf("%d\n",dp[n][1]);
    return 0;
}

