#include <cstdio>
#include <cstring>
const int size=2501;
struct Edge{
	int to,next,w;
} E[12401];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[size],q[size];
bool flag[size]={};
void SPFA(int s){
	memset(dis,0x3f,sizeof(dis));
	q[0]=s,flag[s]=true,dis[s]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next)
			if(dis[E[i].to]>dis[u]+E[i].w){
				dis[E[i].to]=dis[u]+E[i].w;
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					q[e]=E[i].to;
					e=(e+1)%size;
				}
			}
	}
}
int main(){
	int n,m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	SPFA(s);
	printf("%d\n",dis[t]);
	return 0;	
}

