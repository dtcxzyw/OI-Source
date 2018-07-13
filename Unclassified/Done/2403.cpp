#include <cstdio>
#include <cstring>
#include <map>
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
const int size=100100;
struct G{
	struct Edge{
		int to,next;
	} E[size*70];
	int last[size],cnt;
	G():cnt(0){
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
	}
} g1,g2;
int dfn[size]={},low[size],st[size],top=0,col[size],siz[size],cnt=0,cc=0;
bool flag[size]={};
void DFS(int u){
	dfn[u]=low[u]=++cnt;
	flag[u]=true;
	st[++top]=u;
	for(int i=g1.last[u];i;i=g1.E[i].next){
		int v=g1.E[i].to;
		if(!dfn[v]){
			DFS(v);
			if(low[v]<low[u])low[u]=low[v];
		}
		else if(flag[v] && dfn[v]<low[u])
			low[u]=dfn[v];
	}
	if(low[u]==dfn[u]){
		int c=++cc,v;
		siz[c]=0;
		do{
			v=st[top--];
			++siz[c];
			flag[v]=false;
			col[v]=c;
		}while(v!=u);
	}
}
int in[size]={},order[size],dp[size]={};
void topSort(int n){
	int p=0;
	for(int i=1;i<=n;++i)
		if(in[i]==0)
			order[++p]=i;
	for(int i=1;i<=p;++i){
		int u=order[i];
		for(int j=g2.last[u];j;j=g2.E[j].next){
			int v=g2.E[j].to;
			if(--in[v]==0)
				order[++p]=v;
		}
	}
}
struct Info{
	int x,y,t;
} A[size];
std::multimap<int,int> hx,hy;
typedef std::multimap<int,int>::iterator Iter;
typedef std::pair<Iter,Iter> Range;
bool near(int a,int b){
	return (a>b?a-b:b-a)<=1;
}
int main(){
	int n=read();
	int r=read();
	int c=read();
	for(int i=1;i<=n;++i){
		A[i].x=read();
		A[i].y=read();
		A[i].t=read();
		hx.insert(std::make_pair(A[i].x,i)); 
		hy.insert(std::make_pair(A[i].y,i));
	}
	for(int i=1;i<=n;++i){
		if(A[i].t==1){
			Range r=hx.equal_range(A[i].x);
			for(Iter j=r.first;j!=r.second;++j)
				if(j->second!=i)
					g1.addEdge(i,j->second); 
		}
		else if(A[i].t==2){
			Range r=hy.equal_range(A[i].y);
			for(Iter j=r.first;j!=r.second;++j)
				if(j->second!=i)
					g1.addEdge(i,j->second); 
		}
		else{
			Iter begin=hx.lower_bound(A[i].x-1);
			Iter end=hx.upper_bound(A[i].x+1);
			for(Iter j=begin;j!=end;++j)
				if(j->second!=i && near(A[j->second].y,A[i].y))
					g1.addEdge(i,j->second); 
		}
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			DFS(i);
	for(int i=1;i<=n;++i)
		for(int j=g1.last[i];j;j=g1.E[j].next){
			int v=g1.E[j].to;
			if(col[i]!=col[v])
				g2.addEdge(col[i],col[v]),++in[col[v]]; 
		}
	topSort(cc);
	int ans=0;
	for(int i=1;i<=cc;++i){
		int u=order[i];
		dp[u]+=siz[u];
		if(dp[u]>ans)ans=dp[u];
		for(int j=g2.last[u];j;j=g2.E[j].next){
			int v=g2.E[j].to;
			if(dp[v]<dp[u])dp[v]=dp[u];
		}
	}
	printf("%d\n",ans);
	return 0;
}

