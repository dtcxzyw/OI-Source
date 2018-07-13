#include <cstdio>
#include <cstring>
const int size=101;
long long link[size][size],cnt[size][size]={};
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    memset(link,0x3f,sizeof(link));
    int u,v,w;
    for(int i=0;i<m;++i){
        scanf("%d%d%d",&u,&v,&w);
        link[u][v]=link[v][u]=w;
        cnt[u][v]=cnt[v][u]=1;
    }
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)if(i!=k)
            for(int j=1;j<=n;++j)if(i!=j && j!=k){
                long long nd=link[i][k]+link[k][j];
                if(link[i][j]>nd)link[i][j]=nd,cnt[i][j]=0;
                if(link[i][j]==nd)cnt[i][j]+=cnt[i][k]*cnt[k][j];
            }
    for(int k=1;k<=n;++k){
        double ans=0.0;
        for(int i=1;i<=n;++i)if(i!=k)
            for(int j=1;j<=n;++j)if(i!=j && j!=k && link[i][j]==link[i][k]+link[k][j])
                ans+=1.0*cnt[i][k]*cnt[k][j]/cnt[i][j];
        printf("%.3lf\n",ans);
    }
    return 0;
}

