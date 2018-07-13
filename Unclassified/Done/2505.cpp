#include <cstdio>
#include <cstring>
const int size=1510,mod=1000000007;
struct Edge{
	int src,to,next,w;
}E[5010];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].src=u,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool flag[size],mark[5010];
int q[size],dis[size];
void SPFA(int s,int m){
	memset(flag,0,sizeof(flag));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,flag[s]=true,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(dis[v]>dis[u]+E[i].w){
				dis[v]=dis[u]+E[i].w;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
	for(int i=1;i<=m;++i)
		mark[i]=(dis[E[i].src]+E[i].w==dis[E[i].to]);
}
int begin[size],end[size],in[size];
void top(int m,int s){
	memset(begin,0,sizeof(begin));
	memset(end,0,sizeof(end));
	memset(in,0,sizeof(in));
	int b=0,e=1;
	q[b]=s,end[s]=1;
	for(int i=1;i<=m;++i)if(mark[i])++in[E[i].to];
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next)
			if(mark[i]){
				int v=E[i].to;
				if(--in[v]==0)q[e++]=v;
				end[v]=(end[v]+end[u])%mod;
			}
	}
	for(int i=e-1;i>=0;--i){
		int u=q[i];
		++begin[u];
		for(int j=last[u];j;j=E[j].next)
			if(mark[j])
				begin[u]=(begin[u]+begin[E[j].to])%mod;
	}
}
int res[5010]={};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
	}
	for(int i=1;i<=n;++i){
		SPFA(i,m);
		top(m,i);
		for(int j=1;j<=m;++j)if(mark[j])
			res[j]=(res[j]+1LL*begin[E[j].to]*end[E[j].src])%mod;
	}
	for(int i=1;i<=m;++i)printf("%d\n",res[i]);
	return 0;
}

