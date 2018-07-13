#include <cstdio>
#include <cstring>
struct Edge{
	int to,next,w;
} E[600];
const int size=250;
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int ans=0,dis[size],ucnt[size]={},q[size];
bool flag[size];
bool SPFA(int s,int n,int d){
	memset(dis,0xc0,sizeof(dis));
	int b=0,e=1;
	q[0]=s,dis[s]=d,flag[s]=true;
	if(ans<d)ans=d;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		if(++ucnt[u]>n)return false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			int nd=dis[u]+d+E[i].w;
			if(dis[v]<nd){
				dis[v]=nd;
				if(ans<nd)ans=nd;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
	return true;
}
int main(){
	int d,p,c,f,s;
	scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
	int u,v,w;
	
	for(int i=0;i<p;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v,0);
	}
	
	for(int i=0;i<f;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,-w);
	}
	
	if(SPFA(s,c,d))printf("%d\n",ans);
	else puts("-1");
	
	return 0;
}

