#include <cstdio>
#include <algorithm>
struct Info{
    long long a,b,c;
    bool operator<(const Info& rhs) const{
        return rhs.b*c<b*rhs.c;
    }
} A[51];
long long dp[100001]={};
int main(){
    int t,n;
    scanf("%d%d",&t,&n);
    for(int i=1;i<=n;++i)
        scanf("%lld",&A[i].a);
    for(int i=1;i<=n;++i)
        scanf("%lld",&A[i].b);
    for(int i=1;i<=n;++i)
        scanf("%lld",&A[i].c);
    std::sort(A+1,A+n+1);
    for(int i=1;i<=n;++i)
        for(int j=t;j>=A[i].c;--j)
            dp[j]=std::max(dp[j],dp[j-A[i].c]+A[i].a-A[i].b*j);		
    long long ans=0;
    for(int i=0;i<=t;++i)
        ans=std::max(ans,dp[i]);
    printf("%lld\n",ans);
    return 0;
}

