#include <cstdio>
const int size=2001;
struct Edge{
	int to,next;
	double w;
} E[size*size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=100.0/(100.0-w);
	last[u]=cnt;
}
double dis[size];
int q[size];
bool flag[size]={};
void SPFA(int n,int s){
	for(int i=1;i<=n;++i)dis[i]=1e10;
	dis[s]=100.0,q[0]=s,flag[s]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			double nd=dis[u]*E[i].w;
			int v=E[i].to;
			if(dis[v]>nd){
				dis[v]=nd;
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
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	int s,t;
	scanf("%d%d",&s,&t);
	SPFA(n,s);
	printf("%.8lf",dis[t]);
	return 0;
}

