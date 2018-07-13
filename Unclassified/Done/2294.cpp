#include <cstdio>
#include <cstring>
const int size=102,SS=101;
struct Edge{
	int to,next,w;
} E[3001];
int last[size],cnt;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool flag[size],ans;
int dis[size];
void init(){
	memset(last,0,sizeof(last));
	cnt=0;
	memset(flag,0,sizeof(flag));
	memset(dis,0x3f,sizeof(dis));
	dis[SS]=0;
	ans=true;
}
void DFS(int x){
	if(flag[x]){
		ans=false;
		return;
	}
	flag[x]=true;
	for(int i=last[x];i;i=E[i].next)
		if(dis[x]+E[i].w<dis[E[i].to]){
			dis[E[i].to]=dis[x]+E[i].w;
			DFS(E[i].to);
			if(!ans)return;
		}
	flag[x]=false;
}
void foo(){
	int n,m;
	scanf("%d%d",&n,&m);
	init();
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		--u;
		//W(t)-W(s-1)==w
		//W(v)-W(u)<=w && W(v)-W(u)>=w
		//W(v)-W(u)<=w && W(u)-W(v)<=-w
		addEdge(u,v,w);
		addEdge(v,u,-w);
	}
	for(int i=0;i<=n;++i)
		addEdge(SS,i,0);
	DFS(SS);
	puts(ans?"true":"false");
}
int main(){
	int w;
	scanf("%d",&w);
	while(w--)foo();
	return 0;
}

