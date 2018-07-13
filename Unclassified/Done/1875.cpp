#include <cstdio>
const int size=1010;
int dis[size],cnt[size];
struct Edge{
	int with,next,to;
} E[size*size];
int last[size]={},ecnt=0;
bool linked[size][size]={};
void addEdge(int u,int v,int w){
	if(linked[u][v])return;
	linked[u][v]=true;
	++ecnt;
	E[ecnt].with=v,E[ecnt].to=w,E[ecnt].next=last[u];
	last[u]=ecnt;
}
bool flag[size]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&dis[i]);
		cnt[i]=1;
	}
	int u,v,w;
	while(scanf("%d%d%d",&u,&v,&w)!=EOF){
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	
	for(int i=1;i<n;++i){
		int minv=1<<30;
		for(int j=0;j<n;++j)
			if(!flag[j] && dis[j]<minv)
				minv=dis[j],u=j;
		flag[u]=true;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].with;
			if(flag[v]){
				int nd=dis[u]+dis[v],w=E[i].to;
				if(nd<dis[w])cnt[w]=0,dis[w]=nd;
				if(nd==dis[w])
					cnt[w]+=cnt[u]*cnt[v];
			}
		}
	}
	
	printf("%d %d\n",dis[0],cnt[0]);
	return 0;
}

