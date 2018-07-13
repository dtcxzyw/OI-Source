#include <cstdio>
#include <cstring>
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
const int size=1010,SS=1008;
struct Edge{
    int to,next;
} E[size*size];
int last[size]={},cnt=0;
bool linked[size][size]={};
void addEdge(int u,int v){
	if(linked[u][v])return;
    linked[u][v]=true;
	++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
bool flag[size];
int dis[size]={},q[size];
void SPFA(int n){
    memset(flag,0,sizeof(flag));
    int b=0,e=1;
    q[0]=SS,flag[SS]=true;
    while(b!=e){
        int u=q[b];
        flag[u]=false;
        b=(b+1)%size;
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            if(dis[u]>=dis[v]){
                dis[v]=dis[u]+1;
                if(!flag[v]){
                    flag[v]=true;
                    q[e]=v;
                    e=(e+1)%size;
                }
            } 
        }
    }
}
int A[size];
int main(){
    int n=read();
    int m=read();
    for(int i=1;i<=n;++i)
        addEdge(SS,i);
    for(int i=0;i<m;++i){
        int k=read();
        memset(flag,0,sizeof(flag));
        for(int j=1;j<=k;++j){
            A[j]=read();
            flag[A[j]]=true;
        }
        
        for(int j=1;j<=k;++j)
            for(int x=A[1];x<=A[k];++x)
                if(!flag[x])
                    addEdge(x,A[j]);
    }
    SPFA(n);
    int ans=1;
    for(int i=1;i<=n;++i)
        if(ans<dis[i])
            ans=dis[i];
    printf("%d\n",ans);
    return 0;
}

