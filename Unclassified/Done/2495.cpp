#include <cstdio>
#include <cstring>
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
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	printImpl(x);
	putchar('\n');
}
const int size=250100;
struct G{
	struct Edge{
		int to,next,w;
	} E[size*2];
	int last[size],cnt;
	G():cnt(0){
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v,int w){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
		last[u]=cnt;
	}
} g1,g2;
int id[size],p[size][20],d[size],icnt=0;
long long w[size];
void DFS(int u){
	id[u]=++icnt;
	for(int i=1;i<20;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=g1.last[u];i;i=g1.E[i].next){
		int v=g1.E[i].to;
		if(v!=p[u][0]){
			p[v][0]=u,d[v]=d[u]+1,w[v]=std::min(w[u],static_cast<long long>(g1.E[i].w));
			DFS(v);
		}
	}	
}
int lca(int u,int v){
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
int pos[size],st[size];
bool cmp(int a,int b){
	return id[a]<id[b];
}
long long dp(int u){
	if(!g2.last[u])return w[u];
	long long res=0;
	for(int i=g2.last[u];i;i=g2.E[i].next)
		res+=dp(g2.E[i].to);
	g2.last[u]=0;
	return std::min(res,w[u]);
}
int main(){
	int n=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		int w=read();
		g1.addEdge(u,v,w);
		g1.addEdge(v,u,w);
	}
	p[1][0]=0,d[1]=1,w[1]=1LL<<60;
	DFS(1);
	int m=read();
	for(int i=0;i<m;++i){
		int k=read();
		for(int i=1;i<=k;++i)pos[i]=read();
		std::sort(pos+1,pos+k+1,cmp);
		int cnt=1;
		for(int i=2;i<=k;++i)
			if(lca(pos[cnt],pos[i])!=pos[cnt])pos[++cnt]=pos[i];
		g2.cnt=0;
		int top=1;
		st[top]=1;
		for(int i=1;i<=cnt;++i){
			int p=lca(st[top],pos[i]);
			while(d[p]<d[st[top]]){
				if(d[st[top-1]]<=d[p]){
					g2.addEdge(p,st[top--],0);
					if(st[top]!=p)st[++top]=p;
					break;
				}
				g2.addEdge(st[top-1],st[top],0);
				--top;
			}
			if(st[top]!=pos[i])st[++top]=pos[i];
		}
		while(top>1){
			g2.addEdge(st[top-1],st[top],0);
			--top;
		}
		print(dp(1));
	}
	return 0;
}

