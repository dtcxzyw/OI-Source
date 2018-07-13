#include <cstdio>
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
const int size=500010;
struct Edge{
	int to,next;
} E[2][size];
int last[2][size]={},cnt[2]={};
void addEdge(int u,int v,int id){
	++cnt[id];
	E[id][cnt[id]].to=v,E[id][cnt[id]].next=last[id][u];
	last[id][u]=cnt[id];
}
int c[size],dfn[size],low[size],sta[size],stc=0,pc=0,bcnt=0,col[size],w[size];
bool flag[size]={};
void DFS(int u){
	flag[u]=true;
	sta[++stc]=u;
	dfn[u]=low[u]=++pc;
	for(int i=last[0][u];i;i=E[0][i].next){
		int v=E[0][i].to;
		if(dfn[v]){
			if(flag[v] && dfn[v]<low[u])low[u]=dfn[v];
		}
		else{
			DFS(v);
			if(low[v]<low[u])low[u]=low[v];
		}
	}
	if(dfn[u]==low[u]){
		++bcnt;
		w[bcnt]=0;
		int v;
		do{
			v=sta[stc--];
			col[v]=bcnt;
			w[bcnt]+=c[v];
			flag[v]=false;
		}
		while(u!=v);
	}
}
void pre(int s,int n){
	DFS(s);
	for(int i=1;i<=n;++i)
		for(int j=last[0][i];j;j=E[0][j].next){
			int v=E[0][j].to;
			if(col[i]!=col[v])
				addEdge(col[i],col[v],1);
		}
}
int dis[size]={},q[size];
void SPFA(int s){
	memset(flag,0,sizeof(flag));
	q[0]=s,dis[s]=w[s],flag[s]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[1][u];i;i=E[1][i].next){
			int v=E[1][i].to;
			if(dis[v]<dis[u]+w[v]){
				dis[v]=dis[u]+w[v];
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
}
int main(){
	int n=read();
	int m=read();
	int u,v;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		addEdge(u,v,0);
	}
	for(int i=1;i<=n;++i)c[i]=read();
	int s=read();
	pre(s,n);
	SPFA(col[s]);
	int k=read();
	int ans=0;
	for(int i=0;i<k;++i)
		ans=std::max(ans,dis[col[read()]]);
	printf("%d\n",ans);
	return 0;
}

