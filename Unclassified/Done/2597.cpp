#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
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
const int size=65536;
int p[size][18]={},in[size]={},order[size]={},d[size]={},siz[size]={};
std::vector<int> fa[size];
struct G{
	struct Edge{
		int to,next;
	} E[size<<6];
	int last[size],cnt;
	G(){
		cnt=0;
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
	}
	int lca(int u,int v){
		if(d[u]<d[v])std::swap(u,v);
		int delta=d[u]-d[v];
		for(int i=0;i<18;++i)
			if(delta&(1<<i))
				u=p[u][i];
		if(u==v)return u;
		for(int i=17;i>=0;--i)
			if(p[u][i]!=p[v][i])
				u=p[u][i],v=p[v][i];
		return p[u][0];
	}
	void update(int u){
		int cp=fa[u][0];
		for(int k=1;k<fa[u].size();++k)
			cp=lca(cp,fa[u][k]);
		d[u]=d[cp]+1;
		p[u][0]=cp;
		for(int i=1;i<18;++i)
			p[u][i]=p[p[u][i-1]][i-1];
	}
	void top(){
		int siz=1;
		order[1]=0;
		for(int i=1;i<=siz;++i){
			int u=order[i];
			for(int j=last[u];j;j=E[j].next){
				int v=E[j].to;
				if(--in[v]==0){
					order[++siz]=v;
					update(v);
				}
			}
		}
	}
	void dp(int u){
		siz[u]=1;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			dp(v);
			siz[u]+=siz[v];
		}
	}
} g1,g2;
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		while(true){
			int v=read();
			if(v)g1.addEdge(v,i),++in[i],fa[i].push_back(v);
			else break;
		}
	}
	for(int i=1;i<=n;++i)
		if(!in[i])
			g1.addEdge(0,i),++in[i],fa[i].push_back(0);
	g1.top();
	for(int i=1;i<=n;++i)
		g2.addEdge(p[i][0],i);
	g2.dp(0);
	for(int i=1;i<=n;++i)
		print(siz[i]-1);	
	return 0;
}

