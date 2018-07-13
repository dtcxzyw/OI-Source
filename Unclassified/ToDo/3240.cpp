#include <cstdio>
#include <cstring>
const int size=105,mod=1000000007;
struct G{
	struct Edge{
		int to,next,w;
	} E[size];
	int last[size],cnt;
	void clear(){
		memset(last,0,sizeof(last));
		cnt=0;
	}
	void addEdge(int u,int v){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u]
	}
} g1,g2;
int fa[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool vis[size]={};
bool findRing(int u){
	vis[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(vis[v])return true;
		if(findRing(v))return true;
	}
	vis[u]=false;
	return false;
}
int id[size];
long long fac[size],dp[size][size]={}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	fac[0]=1;
	for(int i=1;i<=n;++i){
		fa[i]=i;
		fac[i]=fac[i-1]*i%mod;
	}
	g1.clear();
	for(int i=1;i<=m;++i){
		int x,y;
		char op[2];
		scanf("%d %s %d",&x,op,&y);
		if(op[0]=='='){
			x=find(x),y=find(y);
			if(x!=y)fa[x]=y;
		}
		else g1.addEdge(y,x);
	}
	g2.clear();
	for(int i=1;i<=n;++i){
		int fi=find(i);
		for(int j=last[i];j;j=E[j].next){
			int v=E[j].to;
			int fv=find(v);
			if(fi==fv){
				puts("0");
				return;
			}
			g2.addEdge(fi,fv); 
		}
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		if(find(i)==i){
			id[++cnt]=i;
			if(findRing(i)){
				puts("0");
				return 0;
			}
		}
	for(int i=1;i<=cnt;++i)
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j){
			for(int k=0;k<=cnt;++k){
				
			}
		}
	return 0;
}

