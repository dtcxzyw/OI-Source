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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar(' ');
}
const int size=300100;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	if(u && u!=v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
	}
}
int p[size][20],d[size],dfn[size],siz[size],dcnt=0;
void DFS(int u){
	dfn[u]=++dcnt;
	siz[u]=1;
	for(int i=1;i<20;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u][0]!=v){
			p[v][0]=u;
			d[v]=d[u]+1;
			DFS(v);
			siz[u]+=siz[v];
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
int dis(int u,int v){
	return d[u]+d[v]-(d[lca(u,v)]<<1);
}
int col[size]={},rsiz[size],dp[size]={},rank[size],pcnt;
void DFSup(int u,int p){
	rank[++pcnt]=u;
	rsiz[u]=siz[u];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p){
			DFSup(v,u);
			if(col[v]){
				if(col[u]){
					int d1=dis(col[u],u),d2=dis(col[v],u);
					if(d1>d2 || (d1==d2 && col[v]<col[u]))col[u]=col[v];
				}
				else col[u]=col[v];
			}
		}
	}
}
void DFSdown(int u,int p){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p){
			if(col[v]){
				int d1=dis(col[u],v),d2=dis(col[v],v);
				if(d1<d2 || (d1==d2 && col[u]<col[v]))col[v]=col[u];
			}
			else col[v]=col[u];
			DFSdown(v,u);
		}
	}
}
void calc(int fa,int u){
	int son=u,delta=d[u]-d[fa]-1;
	for(int i=0;i<20;++i)
		if(delta&(1<<i))
			son=p[son][i];
	rsiz[fa]-=siz[son];
	if(col[u]==col[fa])dp[col[u]]+=siz[son]-siz[u];
	else{
		int mid=u;
		for(int i=19;i>=0;--i){
			int f=p[mid][i];
			if(d[f]>d[fa]){
				int d1=dis(col[fa],f),d2=dis(col[u],f);
				if(d1>d2 || (d1==d2 && col[u]<col[fa]))mid=f;
			}
		}	
		dp[col[u]]+=siz[mid]-siz[u];
		dp[col[fa]]+=siz[son]-siz[mid];
	}
}
int A[size],order[size],st[size];
bool cmp(int u,int v){
	return dfn[u]<dfn[v];
}
void foo(){
	int m=read();
	for(int i=0;i<m;++i){
		A[i]=read();
		order[i]=col[A[i]]=A[i];
	}
	std::sort(A,A+m,cmp);
	int top=0;
	if(col[1]!=1)
		st[++top]=1;
	for(int i=0;i<m;++i){
		if(top){
			int x=lca(st[top],A[i]);
			while(true){
				if(d[st[top-1]]<=d[x]){
					addEdge(x,st[top--]);
					if(st[top]!=x)st[++top]=x;
					break;
				}
				addEdge(st[top-1],st[top]);
				--top;
			}
			if(st[top]!=A[i])st[++top]=A[i];
		}
		else st[++top]=A[i];
	}
	while(top>1){
		addEdge(st[top-1],st[top]);
		--top;
	}
	pcnt=0;
	DFSup(1,0);
	DFSdown(1,0);
	for(int i=1;i<=pcnt;++i){
		int u=rank[i];
		for(int j=last[u];j;j=E[j].next)
			calc(u,E[j].to);
	}
	for(int i=1;i<=pcnt;++i){
		int u=rank[i];
		dp[col[u]]+=rsiz[u];
	}
	for(int i=0;i<m;++i)
		print(dp[order[i]]);
	puts("");
	cnt=0;
	for(int i=1;i<=pcnt;++i){
		int u=rank[i];
		last[u]=col[u]=rsiz[u]=dp[u]=0;
	}
}
int main(){
	int n=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	memset(last,0,sizeof(last));
	cnt=0;
	int q=read();
	for(int i=0;i<q;++i)foo();
	return 0;
}

