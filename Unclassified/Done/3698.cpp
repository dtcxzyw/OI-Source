#include <cstdio>
const int size=110;
struct Edge{
	int to,next;
} E[300];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int f[size][size]={},g[size][size]={};
int maxv(int a,int b){
	return a>b?a:b;
}
void DFS(int u,int n,int p){
	f[u][0]=g[u][0]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v){
			DFS(v,n-1,u);
			for(int j=n;j>=0;--j)
				for(int k=0;k<j;++k){
					if(j-k>=2){
						g[u][j]=maxv(g[u][j],g[u][k]+g[v][j-k-2]);
						f[u][j]=maxv(f[u][j],f[u][k]+g[v][j-k-2]);
					}
					f[u][j]=maxv(f[u][j],g[u][k]+f[v][j-k-1]);
				}
		}
	}
	for(int i=1;i<=n;++i){
		g[u][i]=maxv(g[u][i],g[u][i-1]);
		f[u][i]=maxv(f[u][i],f[u][i-1]);
	}
}
int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(0,n,-1);
	printf("%d\n",f[0][n]);
	return 0;
}

