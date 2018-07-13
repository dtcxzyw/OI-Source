#include <cstdio>
#include <cmath>
#include <cstring>
typedef double FT;
struct Bird{
    int flag;
    FT a,b;
} B[18*18];
const FT eps=1e-6;
struct Pig{
    FT x,y,k;
    bool hit(Pig rhs,Bird& res) const{
        if (x!=rhs.x){
            res.a=(k-rhs.k)/(x-rhs.x);
            if (res.a<0.0){
                res.b=k-res.a*x;
                return true;
            }
        }
        return false;
    }
    int test(Bird bird) const{
        FT d=(bird.a*x+bird.b)*x-y;
        return fabs(d)<=eps;
    }
} P[18];
int dp[1<<18],bc[1<<18];
void foo(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i){
        scanf("%lf%lf",&P[i].x,&P[i].y);
        P[i].k=P[i].y/P[i].x;
    }
    int bcnt=1;
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
            if(P[i].hit(P[j],B[bcnt])){
                B[bcnt].flag=((1<<i)|(1<<j));
                ++bcnt;
            }
    for(int i=1;i<bcnt;++i){
        for(int j=0;j<n;++j)
            B[i].flag|=(P[j].test(B[i])<<j);
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0;
    int maxs=1<<n;
    for(int i=1;i<bcnt;++i){
        for(int j=0;j<maxs;++j){
            int obj=j|B[i].flag;
            if(dp[obj]>dp[j]+1)
                dp[obj]=dp[j]+1;
        }
    }
    int ans=n;
    for(int i=0;i<maxs;++i){
        int siz=(n-bc[i])+dp[i];
        if(siz<ans)ans=siz;
    }
    printf("%d\n",ans);
}
int main(){
    for(int i=0;i<(1<<18);++i)
        bc[i]=bc[i>>1]+(i&1);
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;++i)foo();
    return 0;
}

