#include <cstdio>
#include <cstring>
#include <cmath>
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
const int size=111;
struct G{
	struct Edge{
		int to,next;
		double f;
	} E[2015];
	int last[size],cnt;
	G(){
		memset(last,0,sizeof(last));
		cnt=1;
	}
	void addEdgeImpl(int u,int v,int f){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
		last[u]=cnt;
	}
	void addEdge(int u,int v,int f){
		addEdgeImpl(u,v,f);
		addEdgeImpl(v,u,0);
	}
} g1,g2;
const double eps=1e-10;
int n,q[size],d[size];
bool BFS(){
	memset(d,0,sizeof(d));
	d[1]=1,q[0]=1;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=g2.last[u];i;i=g2.E[i].next){
			int v=g2.E[i].to;
			if(g2.E[i].f>eps && !d[v]){
				d[v]=d[u]+1;
				q[e++]=v;	
			}
		}
	}
	return d[n];
}
int now[size];
double DFS(int u,double f){
	if(u==n || f<eps)return f;
	double res=0.0,k;
	for(int i=now[u];i;i=g2.E[i].next){
		int v=g2.E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,fmin(f,g2.E[i].f)))>=eps){
			g2.E[i].f-=k,g2.E[i^1].f+=k;
			res+=k,f-=k;
			if(fabs(f)<eps)break;
		}
	}
	if(res<eps)d[u]=0;
	return res;
}
double dinic(double k){
	memcpy(&g2,&g1,sizeof(g2));
	for(int i=2;i<=g2.cnt;i+=2)
		g2.E[i].f=fmin(g2.E[i].f,k);
	double res=0;
	while(BFS()){
		memcpy(now,g2.last,sizeof(now));
		res+=DFS(1,1e10);
	}
	return res;
}
int main(){
	n=read();
	int m=read();
	int p=read();
	double l=0.0,r=0.0;
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int f=read();
		g1.addEdge(u,v,f);
		if(f>r)r=f;
	}
	double ans=dinic(1e10);
	while(r-l>=eps){
		double mid=(l+r)*0.5;
		if(fabs(ans-dinic(mid))<eps)r=mid;
		else l=mid;
	}
	printf("%d\n%.8lf\n",static_cast<int>(ans+0.5),l*p);
	return 0;
}

