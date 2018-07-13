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
const int size=1005;
struct G{
	struct Edge{
		int to,next;
		long long w;
	} E[size*size];
	int last[size],cnt;
	void init(){
		memset(last,0,sizeof(last));
		cnt=1;
	}
	void addEdge(int u,int v,long long w){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
		last[u]=cnt;
	}
	void addFlow(int u,int v,long long f){
		addEdge(u,v,f);
		addEdge(v,u,0);
	}
} g1,g2;
long long dis[2][size];
int q[size];
bool flag[size]={};
void SPFA(int s,int id){
	memset(dis[id],0x3f,sizeof(dis[id]));
	q[0]=s,dis[id][s]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=g1.last[u];i;i=g1.E[i].next){
			int v=g1.E[i].to;
			long long nd=dis[id][u]+g1.E[i].w;
			if(nd<dis[id][v]){
				dis[id][v]=nd;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
}
int d[size],n;
bool BFS(){
	memset(d,0,sizeof(d));
	d[1+n]=1,q[0]=1+n;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=g2.last[u];i;i=g2.E[i].next){
			int v=g2.E[i].to;
			if(g2.E[i].w && !d[v]){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[n];
}
int now[size];
long long minv(long long a,long long b){
	return a<b?a:b;
}
long long DFS(int u,long long f){
	if(u==n || f==0)return f;
	long long res=0,k;
	for(int& i=now[u];i;i=g2.E[i].next){
		int v=g2.E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,g2.E[i].w)))){
			g2.E[i].w-=k,g2.E[i^1].w+=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	if(res==0)d[u]=0;
	return res;
}
long long dinic(){
	long long res=0;
	while(BFS()){
		memcpy(now,g2.last,sizeof(now));
		res+=DFS(1+n,1LL<<60);
	}
	return res;
}
int main(){
	n=read();
	int m=read();
	g1.init();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int w=read();
		g1.addEdge(u,v,w);
		g1.addEdge(v,u,w);
	}
	SPFA(1,0);
	SPFA(n,1);
	long long mind=dis[0][n];
	g2.init();
	for(int i=2;i<=g1.cnt;++i){
		int u=g1.E[i^1].to;
		int v=g1.E[i].to;
		if(dis[0][u]+g1.E[i].w+dis[1][v]==mind)
			g2.addFlow(u+n,v,1LL<<60);
	}
	for(int i=1;i<=n;++i)
		g2.addFlow(i,i+n,read());
	printf("%lld\n",dinic());
	return 0;
}

