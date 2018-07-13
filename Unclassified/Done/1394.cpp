#include <cstdio>
bool link[301][301]={},flag[301]={};
int h[301],n,cnt=0;
void DFS(int x){
	if(flag[x])return;
	flag[x]=true;
	++cnt;
	for(int i=1;i<=n;++i)
		if(link[x][i])
			DFS(i);
}
int main(){
	int m;
	scanf("%d%d",&n,&m);
	int maxh=0,mi;
	for(int i=1;i<=n;++i){
		scanf("%d",&h[i]);
		if(maxh<h[i])
			maxh=h[i],mi=i;
	}
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		if(h[u]>h[v])link[u][v]=true;
		else if(h[v]>h[u])link[v][u]=true;
	}
	DFS(mi);
	if(cnt==n) printf("Oui, j'ai trouve la solution.\n%d\n",mi);
	else puts("Non");
	return 0;
}

