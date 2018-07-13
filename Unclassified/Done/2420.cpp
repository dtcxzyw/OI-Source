#include <cstdio>
#include <algorithm>
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
const int size=100001;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int p[size][20]={},w[size][20],d[size];
void DFS(int u){
	for(int i=1;i<20;++i){
		p[u][i]=p[p[u][i-1]][i-1];
		w[u][i]=w[p[u][i-1]][i-1]^w[u][i-1];
	}
	
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!p[v][0]){
			p[v][0]=u;
			w[v][0]=E[i].w;
			d[v]=d[u]+1;
			DFS(v);
		}
	}
}
int LCA(int u,int v){
	int uw=0,vw=0;
	if(d[u]>d[v])std::swap(u,v);
	int dd=d[v]-d[u];
	for(int i=0;i<20;++i)
		if(dd&(1<<i)){
			vw^=w[v][i];
			v=p[v][i];	
		}
		
	for(int i=19;i>=0;--i)
		if(p[u][i]!=p[v][i]){
			uw^=w[u][i],vw^=w[v][i];
			u=p[u][i],v=p[v][i];
		}
		
	if(u!=v){
		uw^=w[u][0];
		vw^=w[v][0];
	}
	
	return uw^vw;
}

void print(int x){
	if(x>=10)print(x/10);
	putchar('0'+x%10);
}

int main(){
	int n=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(1);
	int m=read();
	for(int i=0;i<m;++i){
		print(LCA(read(),read()));
		putchar('\n');	
	}
	return 0;
}

