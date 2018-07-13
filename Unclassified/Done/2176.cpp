#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=101;
struct Edge{
	int to,next,w;
} E[10010];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
long long dis[size];
int prev[size],q[size];
bool flag[size];
void SPFA(int s,int x,int y){
	memset(flag,0,sizeof(flag));
	memset(dis,0x3f,sizeof(dis));
	prev[s]=dis[s]=0,flag[s]=true,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			long long nd=dis[u]+E[i].w;
			if((u==x && v==y) || (u==y && v==x))nd+=E[i].w;
			if(nd<dis[v]){
				dis[v]=nd;
				prev[v]=u;
				if(!flag[v]){
					flag[v]=true;
					if(dis[q[b]]<dis[v]){
						q[e]=v;
						e=(e+1)%size;
					}
					else{
						b=(b-1+size)%size;
						q[b]=v;
					}
				}
			}
		}
	}
}
int p[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	SPFA(1,0,0);
	long long base=dis[n];
	int lcnt=0;
	for(int i=n;i;i=prev[i])
		p[++lcnt]=i;
	long long ans=0;
	for(int i=1;i<lcnt;++i){
		SPFA(1,p[i],p[i+1]);
		ans=std::max(ans,dis[n]-base);
	}
	printf("%lld\n",ans);
	return 0;
}

