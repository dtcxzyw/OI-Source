#include <cstdio>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=500010;
struct Edge{
	int to,next;
} E[2*size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int w[size];
bool flag[size]={};
int d,f[size][25],g[size][25];
const int inf=1<<30;
int minv(int a,int b){
	return a<b?a:b;
}
void DFS(int u,int p){
	if(flag[u])f[u][0]=g[u][0]=w[u];
	for(int i=1;i<=d;++i)g[u][i]=w[u];
	g[u][d+1]=inf;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p){
			DFS(v,u);
			for(int j=d;j>=0;--j)
				g[u][j]=minv(g[u][j]+f[v][j],g[v][j+1]+f[u][j+1]);
			for(int j=d;j>=0;--j)
				g[u][j]=minv(g[u][j],g[u][j+1]);
			f[u][0]=g[u][0];
			for(int j=1;j<=d+1;++j)f[u][j]+=f[v][j-1];
			for(int j=1;j<=d+1;++j)f[u][j]=minv(f[u][j],f[u][j-1]);
		}
	}
}
int main(){
	int n=read();
	d=read();
	for(int i=1;i<=n;++i)w[i]=read();
	int m=read();
	for(int i=0;i<m;++i)flag[read()]=true;
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	printf("%d\n",f[1][0]);
	return 0;
}

