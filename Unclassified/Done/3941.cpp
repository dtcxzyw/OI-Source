#include <cstdio>
inline int read(){
    int res=0,c;
    do c=getchar();
    while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return res;
}
long long sum[401][401]={};
int dp[1000000],mod[401];
int main(){
    int n=read();
    int m=read();
    int k=read();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+read();
            
    long long ans=0;
    for(int bx=0;bx<m;++bx)
        for(int ex=bx+1;ex<=m;++ex){
            for(int y=1;y<=n;++y){
                mod[y]=(sum[y][ex]-sum[y][bx])%k;
                if(mod[y]==0)++ans;
                ans+=(dp[mod[y]]++);
            }
            for(int y=1;y<=n;++y)
            	dp[mod[y]]=0;
        }
        
    printf("%lld\n",ans);
    return 0;
}

