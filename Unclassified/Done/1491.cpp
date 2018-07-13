#include <cstdio>
#include <cmath>
const int size=205;
struct Point{
	int x,y;
	double dis(Point rhs) const{
		int dx=x-rhs.x,dy=y-rhs.y;
		return sqrt(dx*dx+dy*dy);
	}
} points[size];
struct Edge{
	int to,next;
	double w;
} E[100000];
int last[size]={},cnt=0;
void addEdge(int u,int v,double w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int q[size],pre[size]={};
bool flag[size]={};
double dis[size];
void SPFA(int n,int x,int y){
	for(int i=1;i<=n;++i)
		dis[i]=1e10;
	int b=0,e=1;
	q[b]=1;
	dis[1]=0.0;
	flag[1]=true;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			if((u==x && E[i].to==y) || (u==y && E[i].to==x))continue;
			double nd=dis[u]+E[i].w;
			if(dis[E[i].to]>nd){
				dis[E[i].to]=nd;
				pre[E[i].to]=u;
				if(!flag[E[i].to]){
					flag[E[i].to]=true,q[e]=E[i].to;
					e=(e+1)%size;
				}
			}
		}
	}
}
int list[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&points[i].x,&points[i].y);
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		double d=points[u].dis(points[v]);
		addEdge(u,v,d);
		addEdge(v,u,d);
	}
	SPFA(n,0,0);
	if(dis[n]==1e10)puts("-1");
	else{
		int p=n,lcnt=1;
		list[0]=n;
		while(pre[p]){
			list[lcnt++]=pre[p];
			p=pre[p];
		}
		double sd=1e10;
		for(int i=1;i<lcnt;++i){
			SPFA(n,list[i],list[i-1]);
			if(dis[n]<sd)sd=dis[n];
		}
		if(sd==1e10)puts("-1");
		else printf("%.2lf",sd);
	}
	
	return 0;
}

