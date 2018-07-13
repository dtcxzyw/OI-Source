#include <cstdio>
#include <cstring>
const int size=1001;
struct Edge{
	int to,next,w;
} E[size*size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].w=w,E[cnt].next=last[u];
	last[u]=cnt;
}
int dis[size],q[size],pre[size];
bool flag[size];
void SPFA(int x,int y){
	memset(dis,0x3f,sizeof(dis));
	memset(flag,0,sizeof(flag));
	int b=0,e=1;
	flag[1]=true;
	q[0]=1;
	dis[1]=0;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next)
			if(dis[E[i].to]>dis[u]+E[i].w && !((u==x && E[i].to==y) || (u==y && E[i].to==x))){
				dis[E[i].to]=dis[u]+E[i].w;
				pre[E[i].to]=u;
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					q[e]=E[i].to;
					e=(e+1)%size;
				}
			}
	}
}
int list[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	SPFA(0,0);
	int p=n,lcnt=1;
	list[0]=n;
	while(pre[p]){
		list[lcnt++]=pre[p];
		p=pre[p];
	}
	int maxv=0;
	for(int i=1;i<lcnt;++i){
		SPFA(list[i],list[i-1]);
		if(dis[n]>maxv)
			maxv=dis[n];
	}
	
	printf("%d\n",maxv);
	return 0;
}

