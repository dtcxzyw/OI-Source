#include <cstdio>
#include <cstring>
const int size=1510;
struct G{
	struct Edge{
		int to,next,w;
	} E[size*size];
	int last[size],cnt;
	void clear(){
		cnt=0;
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v,int w){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
		last[u]=cnt;
	}
} g1,g2;
int dis[4][size],q[size];
bool flag[size];
void SPFA(int s,int id){
	memset(dis[id],0x3f,sizeof(dis[id]));
	memset(flag,0,sizeof(flag));
	q[0]=s,flag[s]=true,dis[id][s]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=g1.last[u];i;i=g1.E[i].next){
			int v=g1.E[i].to;
			if(dis[id][v]>dis[id][u]+g1.E[i].w){
				dis[id][v]=dis[id][u]+g1.E[i].w;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;	
				}
			}
		}
	}
}
int in[size],dp[size];
int maxv(int a,int b){
	return a>b?a:b;
}
int top(int n){
	memset(dp,0,sizeof(dp));
	int b=0,e=0,res=0;
	for(int i=1;i<=n;++i)
		if(in[i]==0)q[e++]=i;
	while(b!=e){
		int u=q[b++];
		res=maxv(res,dp[u]);
		for(int i=g2.last[u];i;i=g2.E[i].next){
			int v=g2.E[i].to;
			if(--in[v]==0)q[e++]=v;
			dp[v]=maxv(dp[v],dp[u]+g2.E[i].w);
		}
	}
	return res;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int s1,t1,s2,t2;
	scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
	int u,v,w;
	g1.clear();
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		g1.addEdge(u,v,w);
		g1.addEdge(v,u,w);
	}
	SPFA(s1,0);
	SPFA(t1,1);
	SPFA(s2,2);
	SPFA(t2,3);
	memset(in,0,sizeof(in));
	g2.clear();
	for(int i=1;i<=n;++i)
		for(int j=g1.last[i];j;j=g1.E[j].next){
			int v=g1.E[j].to;
			if(dis[0][i]+dis[1][v]+g1.E[j].w==dis[0][t1] && dis[2][i]+dis[3][v]+g1.E[j].w==dis[2][t2])
				g2.addEdge(i,v,g1.E[j].w),++in[v]; 
		}
	int a=top(n);
	memset(in,0,sizeof(in));
	g2.clear();
	for(int i=1;i<=n;++i)
		for(int j=g1.last[i];j;j=g1.E[j].next){
			int v=g1.E[j].to;
			if(dis[0][i]+dis[1][v]+g1.E[j].w==dis[0][t1] && dis[2][v]+dis[3][i]+g1.E[j].w==dis[2][t2])
				g2.addEdge(i,v,g1.E[j].w),++in[v]; 
		}
	int b=top(n);
	printf("%d\n",maxv(a,b));
	return 0;
}

