#include <cstdio>
#include <cstring>
struct Edge{
	int to,next;
} E[10001];
int last[1001]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[101],count[1001]={};
bool flag[1001];
void DFS(int u){
	flag[u]=true;
	++count[u];
	for(int i=last[u];i;i=E[i].next)
		if(!flag[E[i].to])
			DFS(E[i].to);
}
int main(){
	int k,n,m;
	scanf("%d%d%d",&k,&n,&m);
	for(int i=0;i<k;++i)
		scanf("%d",&p[i]);
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
	}
	for(int i=0;i<k;++i){
		memset(flag,0,sizeof(flag));
		DFS(p[i]);
	}
	int ans=0;
	for(int i=1;i<=n;++i)
		ans+=count[i]==k;
	printf("%d\n",ans);
	return 0;
}

