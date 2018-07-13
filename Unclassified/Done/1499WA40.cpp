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
const int size=100005;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool vis[size]={};
int st[size][2],ssiz=0,ring[size][2],rsiz=0;
bool findRing(int u,int src,int d){
	if(vis[u]){
		int v;
		do{
			--ssiz;
			v=st[ssiz][0];
			ring[rsiz][0]=v;
			ring[rsiz][1]=st[ssiz][1];
			++rsiz;
		}
		while(u!=v);
		ring[rsiz-1][1]=d;
		return true;
	}
	st[ssiz][0]=u;
	st[ssiz][1]=d;
	++ssiz;
	vis[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=src && findRing(v,u,E[i].w))return true;
	}
	--ssiz;
	vis[u]=false;
	return false;
}
bool flag[size];
long long dis[2][size]={};
int q[size];
void SPFA(int s,int p){
	memset(dis[p],0x3f,sizeof(dis[p]));
	q[0]=s,dis[p][s]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			long long nd=dis[p][u]+E[i].w;
			if(nd<dis[p][v]){
				dis[p][v]=nd;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
}
double calc(double u,double v,int n){
	double res=0.0;
	for(int i=1;i<=n;++i)
		res=std::max(res,std::min(u+dis[0][i],v+dis[1][i]));
	return res;
}
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		int u=read();
		int v=read();
		int w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	findRing(1,0,0);
	double ans=1e30;
	SPFA(ring[0][0],1);
	for(int i=0;i<rsiz;++i){
		int u=ring[i][0],v=ring[(i+1)%rsiz][0];
		SPFA(v,i&1);
		double len=ring[i][1];
		double l=0.0,r=len;
		while(r-l>=0.01){
			double lm=(l*2.0+r)/3.0;
			double rm=(l+r*2.0)/3.0;
			if(calc(lm,len-lm,n)<calc(rm,len-rm,n))r=rm;
			else l=lm;
		}
		ans=std::min(ans,calc(l,len-l,n));
	}
	printf("%.1lf\n",ans);
	return 0;
}

