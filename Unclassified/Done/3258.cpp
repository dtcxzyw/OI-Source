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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
const int size=300001;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size][20],d[size];
void DFS(int u){
	for(int i=1;i<20;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u][0]!=v){
			p[v][0]=u;
			d[v]=d[u]+1;
			DFS(v);
		}
	}
}
int query(int u,int v){
	if(d[u]<d[v])std::swap(u,v);
	int delta=d[u]-d[v];
	for(int i=0;i<20;++i)
		if(delta&(1<<i))
			u=p[u][i];
	if(u==v)return u;
	for(int i=19;i>=0;--i)
		if(p[u][i]!=p[v][i])
			u=p[u][i],v=p[v][i];
	return p[u][0];
}
int sum[size]={};
void calc(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u][0]!=v){
			calc(v);
			sum[u]+=sum[v];
		}
	}
}
int order[size];
int main(){
	int n=read();
	for(int i=1;i<=n;++i)
		order[i]=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=0;
	DFS(1);
	for(int i=2;i<=n;++i){
		u=order[i];
		v=order[i-1];
		int lca=query(u,v);
		//++sum[u];
		++sum[v];
		--sum[lca];
		--sum[p[lca][0]];
		//--sum[u];
		++sum[p[u][0]];
	}
	calc(1);
	for(int i=1;i<=n;++i)
		print(sum[i]);
	return 0;
}


