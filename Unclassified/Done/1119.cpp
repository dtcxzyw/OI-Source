#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=200;
int t[size],dis[size][size];
void update(int n,int w){
    static int siz=0;
    int last=siz;
    while(siz<n && t[siz]<=w)++siz;
    for(int k=last;k<siz;++k)
        for(int i=0;i<n;++i)
            if(dis[i][k]!=0x3f3f3f3f)
                for(int j=0;j<n;++j)
                    dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i)
        scanf("%d",&t[i]);
    int u,v,w;
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<m;++i){
        scanf("%d%d%d",&u,&v,&w);
        dis[u][v]=dis[v][u]=w;
    }
    int q;
    scanf("%d",&q);
    for(int i=0;i<q;++i){
        scanf("%d%d%d",&u,&v,&w);
        if(t[u]<=w && t[v]<=w){
            update(n,w);
            printf("%d\n",(dis[u][v]==0x3f3f3f3f)?-1:dis[u][v]);
        }
        else puts("-1");
    }
    return 0;
}

