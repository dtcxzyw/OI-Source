#include <cstdio>
#include <algorithm>
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
const int size=1050;
struct Edge{
    int to,next,w;
} E[7000];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
    last[u]=cnt;
}
int q[size],b=0,e=0;
bool flag[size]={};
void push(int* dis,int u){
    if(b!=e && dis[q[b]]>dis[u]){
        b=(b-1+size)%size;
        q[b]=u;
    }
    else{
        q[e]=u;
        e=(e+1)%size;
    }
    flag[u]=true;
}
void SPFA(int* dis){
    while(b!=e){
        int u=q[b];
        flag[u]=false;
        b=(b+1)%size;
        for(int i=last[u];i;i=E[i].next){
            int v=E[i].to;
            if(dis[v]>dis[u]+E[i].w){
                dis[v]=dis[u]+E[i].w;
                if(!flag[v])push(dis,v);
            }
        }
    }
}
int f[size][size];
struct Key{
    int c,id;
} A[15];
int sum[15]={},now[15];
bool check(int s,int p){
	for(int i=1;i<=10;++i)now[i]=0;
	for(int i=0;i<p;++i)if(s&(1<<i))++now[A[i].c];
	for(int i=1;i<=10;++i)if(now[i] && now[i]!=sum[i])return false;
	return true;
}
int dp[size]={};
int main(){
    int n=read();
    int m=read();
    int p=read();
    for(int i=0;i<m;++i){
        int u=read();
        int v=read();
        int w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }	
    for(int i=0;i<p;++i){
        A[i].c=read();
        ++sum[A[i].c];
        A[i].id=read();
    }
    memset(dp,0x3f,sizeof(dp));
    int end=1<<p;
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<p;++i)
    	f[1<<i][A[i].id]=0;
    for(int i=0;i<end;++i){
        for(int j=1;j<=n;++j){
            for(int k=i&(i-1);k;k=(k-1)&i)
                f[i][j]=std::min(f[i][j],f[k][j]+f[i^k][j]);
            if(f[i][j]!=0x3f3f3f3f)push(f[i],j);
        }
        SPFA(f[i]);
    }
    memset(dp,0x3f,sizeof(dp));
    for(int i=0;i<end;++i)
    	for(int j=1;j<=n;++j)
    		dp[i]=std::min(dp[i],f[i][j]);
	for(int i=0;i<end;++i)flag[i]=check(i,p);
    for(int i=0;i<end;++i)if(flag[i])
        for(int j=(i-1)&i;j;j=(j-1)&i)if(flag[j])
            dp[i]=std::min(dp[i],dp[j]+dp[i^j]);
    printf("%d\n",dp[end-1]);
    return 0;
}

