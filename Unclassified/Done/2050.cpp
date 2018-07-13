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
const int size=100100,SS=size-1,ST=size-2;
struct Edge{
    int to,next,c,w;
} E[size*300];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int c,int w){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c,E[cnt].w=w;
    last[u]=cnt;
}
void addEdge(int u,int v,int c,int w){
    addEdgeImpl(u,v,c,w);
    addEdgeImpl(v,u,0,-w);
}
int q[size],dis[size],eid[size],f[size];
bool flag[size];
int minv(int a,int b){
	return a<b?a:b;
}
bool SPFA(){
    memset(dis,0x3f,sizeof(dis));
    memset(flag,0,sizeof(flag));
    q[0]=SS,flag[SS]=true,dis[SS]=0,f[SS]=1<<30;
    int b=0,e=1;
    while(b!=e){
        int u=q[b++];
        if(b==size)b=0;
        flag[u]=false;
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            if(E[i].c>0 && dis[v]>dis[u]+E[i].w){
                dis[v]=dis[u]+E[i].w;
                f[v]=minv(E[i].c,f[u]);
                eid[v]=i;
                if(!flag[v]){
                    flag[v]=true;
                    q[e++]=v;
                    if(e==size)e=0;
                }
            }
        }
    }
    return dis[ST]!=0x3f3f3f3f;
}
int t[50][110],na[size],nb[size];
int MCMF(int sum,int siz,int n){
    int res=0;
    while(SPFA()){
        int p=ST,nf=f[ST];
        res+=nf*dis[ST];
        while(p!=SS){
            E[eid[p]].c-=nf;
            E[eid[p]^1].c+=nf;
            p=E[eid[p]^1].to;
        }
        p=E[eid[ST]^1].to;
        int a=na[p],b=nb[p];
        int end=(a-1)*sum+b;
        addEdge(end,ST,1,0);
        for(int i=1;i<=n;++i)
            addEdge(siz+i,end,1,b*t[i][a]);
    }
    return res;
}
int p[50];
int main(){
    int n=read();
    int m=read();
    int sum=0;
    for(int i=1;i<=n;++i){
        p[i]=read();
        sum+=p[i];
    }
    int siz=sum*m;
    for(int i=1;i<=m;++i)
        addEdge((i-1)*sum+1,ST,1,0);
    for(int i=1;i<=siz;++i)
    	na[i]=(i-1)/sum+1,nb[i]=i%sum+1;
    for(int i=1;i<=n;++i)
        addEdge(SS,siz+i,p[i],0);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            t[i][j]=read();
            addEdge(siz+i,(j-1)*sum+1,1,t[i][j]);
        }
    }
    printf("%d\n",MCMF(sum,siz,n));
    return 0;
}


