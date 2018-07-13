#include <cstdio>
#include <bitset>
#include <cstring>
const int size=2001;
struct G{
	struct Edge{
		int to,next;
	} E[size*size];
	int last[size],cnt;
	void clear(){
		cnt=0;
		memset(last,0,sizeof(last));
	}
	void addEdge(int u,int v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u];
		last[u]=cnt;
	}
} g1,g2;
int dfn[size]={},icnt=0,low[size],col[size],siz[size]={},ccnt=0,st[size],scnt=0;
bool flag[size]={};
void DFS(int u){
	dfn[u]=low[u]=++icnt;
	st[++scnt]=u;
	flag[u]=true;
	for(int i=g1.last[u];i;i=g1.E[i].next){
		int v=g1.E[i].to;
		if(dfn[v]){
			if(flag[v] && dfn[v]<low[u])low[u]=dfn[v];
		}
		else{
			DFS(v);
			if(low[v]<low[u])low[u]=low[v];
		}
	}
	if(dfn[u]==low[u]){
		int c=++ccnt,v;
		do{
			v=st[scnt--];
			flag[v]=false;
			col[v]=c;
			++siz[c];
		}while(u!=v);
	}
}
char buf[size];
int q[size],d[size]={};
std::bitset<size> dp[size]={};
int main(){
	int n;
	scanf("%d",&n);	
	g1.clear();
	for(int i=1;i<=n;++i){
		scanf("%s",buf+1);
		for(int j=1;j<=n;++j)	
			if(buf[j]=='1')
				g1.addEdge(i,j);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			DFS(i);
	g2.clear();
	for(int i=1;i<=n;++i)
		for(int j=g1.last[i];j;j=g1.E[j].next){
			int v=g1.E[j].to;
			if(col[i]!=col[v])
				g2.addEdge(col[i],col[v]),++d[col[v]];
		}
	int qsiz=0;
	for(int i=1;i<=ccnt;++i)
		if(!d[i])
			q[++qsiz]=i;
	for(int i=1;i<=qsiz;++i){
		int u=q[i];
		dp[u][u]=true;
		for(int j=g2.last[u];j;j=g2.E[j].next){
			int v=g2.E[j].to;
			dp[v]|=dp[u];
			if(--d[v]==0)q[++qsiz]=v;
		}
	}
	int res=0;
	for(int i=1;i<=ccnt;++i){
		int sum=0;
		for(int j=1;j<=ccnt;++j)
			if(dp[i][j])
				sum+=siz[j];
		res+=sum*siz[i];
	}
	printf("%d\n",res);
	return 0;
}

