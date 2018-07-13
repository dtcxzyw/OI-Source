#include <cstdio>
#include <vector>
#include <cstring>
const int size=1001;
struct Edge{
    int to,next;
} E[2010];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
int p[size],d[size];
std::vector<int> dv[size];
bool flag[size]={};
void DFS(int u){
    flag[u]=true;
    dv[d[u]].push_back(u);
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(!flag[v]){
            d[v]=d[u]+1,p[v]=u;
            DFS(v);
        }
    }
}
bool cov[size]={};
void color(int u,int d){
    cov[u]=true;
    if(d)
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            color(v,d-1);
        }
}
int main(){
    int n;
    scanf("%d",&n);
    int pi;
    for(int i=2;i<=n;++i){
        scanf("%d",&pi);
        addEdge(pi,i);
        addEdge(i,pi);
    }
    d[1]=0,p[1]=1;
    DFS(1);
    int cnt=0;
    for(int i=size-1;i>=0;--i)
        for(int j=0;j<dv[i].size();++j){
            int u=dv[i][j];
            if(!cov[u]){
                color(p[p[u]],2);
                ++cnt;
            }
        }
    printf("%d\n",cnt);
    return 0;
}

