#include <cstdio>
#include <cstring>
const int size=2005;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size],cnt;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[size];
bool flag[size];
bool DFS(int u){
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(dis[v]>dis[u]+E[i].w){
			dis[v]=dis[u]+E[i].w;
			if(flag[v] || !DFS(v))return false;
		}
	}
	flag[u]=false;
	return true;
}
bool foo(){
	cnt=0;
	memset(last,0,sizeof(last));
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<k;++i){
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		addEdge(x,y+n,-c);
		addEdge(y+n,x,c);
	}
	int num=2*n;
	for(int i=1;i<=num;++i)
		addEdge(0,i,0);
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	memset(flag,0,sizeof(flag));
	return DFS(0);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)puts(foo()?"Yes":"No");
	return 0;
}

