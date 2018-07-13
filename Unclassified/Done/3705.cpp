#include <cstdio>
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
const int size=205,S=size-1,T=size-2;
struct Edge{
    int to,next,f;
    double w;
} E[105*105*2];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=0.0;
    last[u]=cnt;
}
void addEdge(int u,int v){
    addEdgeImpl(u,v);
    addEdgeImpl(v,u);
}
int q[size],eid[size];
double dis[size];
bool flag[size]={};
bool SPFA(){
    for(int i=0;i<size;++i)dis[i]=-1e20;
    dis[S]=0.0,q[0]=S,flag[S]=true;
    int b=0,e=1;
    while(b!=e){
        int u=q[b++];
        if(b==size)b=0;
        flag[u]=false;
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            double nd=dis[u]+E[i].w;
            if(nd>dis[v] && E[i].f){
                dis[v]=nd;
                eid[v]=i;
                if(!flag[v]){
                    flag[v]=true;
                    q[e++]=v;
                    if(e==size)e=0;
                }
            }
        }
    }
    return dis[T]>-1e20;
}
int A[105][105],B[105][105],tmp[size];
bool MCMF(int n,double x){
    int idx=1;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j){
            double w=A[i][j]-x*B[i][j];
            E[++idx].w=w;
            E[++idx].w=-w;
        }
    for(int i=2;i<=cnt;++i)
        E[i].f=1^(i&1);
    double res=0.0;
    while(SPFA()){
        int p=T,ecnt=0,mf=1<<30;
        while(p!=S){
            int e=eid[p];
            tmp[ecnt++]=e;
            int cf=E[e].f;
            if(cf<mf)mf=cf;
            p=E[e^1].to;
        }
        for(int j=0;j<ecnt;++j)
            E[tmp[j]].f-=mf,E[tmp[j]^1].f+=mf;
        res+=dis[T]*mf;
    }
    return res<=0.0;
}
int main(){
    int n=read();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            A[i][j]=read();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            B[i][j]=read();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            addEdge(i,j+n);
    for(int i=0;i<n;++i){
        addEdge(S,i);
        addEdge(i+n,T);
    }
    double l=0.0,r=1e4;
    while(r-l>=1e-7){
        double mid=(l+r)*0.5;
        if(MCMF(n,mid))r=mid;
        else l=mid;
    }
    printf("%.6lf\n",l);
    return 0;
}

