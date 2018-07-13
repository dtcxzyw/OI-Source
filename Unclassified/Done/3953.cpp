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
const int size=100010;
bool flag[size];
int q[size];
struct G{
	struct Edge{
		int to,next,w;
	} E[200010];
	int last[size],cnt,dis[size];
	void reset(){
		cnt=0;
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v,int w){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
		last[u]=cnt;
	}
	void SPFA(int s){
		memset(flag,0,sizeof(flag));
		memset(dis,0x3f,sizeof(dis));
		flag[s]=true,q[0]=s,dis[s]=0;
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
	}
} G1,G2;
int limit,k,p,n,dp[size][51];
bool mark[size][51];
bool DFS(int u,int nk){
	if(mark[u][nk])return true;
	if(~dp[u][nk])return false;
	mark[u][nk]=true;
	dp[u][nk]=(u==n);
	for(int i=G1.last[u];i;i=G1.E[i].next){
		int v=G1.E[i].to;
		int delta=G1.dis[u]+G1.E[i].w+nk-G1.dis[v];
		if(delta<=k && G1.dis[u]+G1.E[i].w+nk+G2.dis[v]<=limit){
			if(DFS(v,delta))return true;
			dp[u][nk]+=dp[v][delta];
			if(dp[u][nk]>=p)dp[u][nk]-=p;
		}
	}
	mark[u][nk]=false;
	return false;
}
void foo(){
	G1.reset();
	G2.reset();
	n=read();
	int m=read();
	k=read();
	p=read();
	int u,v,w;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		G1.addEdge(u,v,w);
		G2.addEdge(v,u,w);		
	}
	G1.SPFA(1);
	G2.SPFA(n);
	limit=G1.dis[n]+k;
	memset(mark,0,sizeof(mark));
	memset(dp,-1,sizeof(dp));
	if(DFS(1,0))puts("-1");
	else printf("%d\n",dp[1][0]);
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)foo();
	return 0;
}

