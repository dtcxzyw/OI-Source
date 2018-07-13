#include <cstdio>
#include <cstring>
const int size=10010;
struct Edge{
    int to,next,w[2];
} E[50010];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
long long dis[2][size];
int q[size*5];
bool flag[size];
void SPFA(int p,int s){
    memset(dis[p],0x3f,sizeof(dis[p]));
    memset(flag,0,sizeof(flag));
    dis[p][s]=0,q[0]=s,flag[s]=true;
    int b=0,e=1;
    while(b!=e){
        int u=q[b++];
        flag[u]=false;
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            long long nd=dis[p][u]+E[i].w[p];
            if(dis[p][v]>nd){
                dis[p][v]=nd;
                if(!flag[v]){
                    flag[v]=true;
                    q[e++]=v;
                }
            }
        }
    }
}
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
int main(){
    int n,m;
    n=read();
    m=read();
    int u,v;
    for(int i=0;i<m;++i){
        u=read();
        v=read();
        addEdge(v,u);
        E[cnt].w[0]=read();
        E[cnt].w[1]=read();
    }
    SPFA(0,n);
    SPFA(1,n);
    for(int i=1;i<=n;++i)
        for(int j=last[i];j;j=E[j].next){
            int v=E[j].to;
			E[j].w[0]=(dis[0][v]-dis[0][i]!=E[j].w[0])+(dis[1][v]-dis[1][i]!=E[j].w[1]);
        }
    SPFA(0,n);
    printf("%lld\n",dis[0][1]);
    return 0;
}

