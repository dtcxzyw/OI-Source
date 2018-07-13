#include <cstdio>
#include <algorithm>
const int size=100001;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int d[size],p[size][20];
int queue[size<<1],qcnt=0,b[size],e[size];
void DFS(int x){
	d[x]=d[p[x][0]]+1;
	for(int i=1;i<20;++i)
		p[x][i]=p[p[x][i-1]][i-1];
	b[x]=++qcnt;
	queue[qcnt]=x;
	for(int i=last[x];i;i=E[i].next)
		if(E[i].to!=p[x][0]){
			p[E[i].to][0]=x;
			DFS(E[i].to);
		}
	e[x]=++qcnt;
	queue[qcnt]=-x;
}
int LCA(int a,int b){
	if(d[a]>d[b])
		std::swap(a,b);
	int delta=d[b]-d[a];
	for(int i=0;i<20;++i)
		if(delta&(1<<i))
			b=p[b][i];
	if(a!=b){
		for(int i=19;i>=0;--i)
			if(p[a][i]!=p[b][i])
				a=p[a][i],b=p[b][i];
		return p[a][0];
	}
	return a;
}
int sum[size<<3|1]={},off[size<<3|1]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)++off[id],sum[id]+=r-l+1;
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr);
		if(m<nr)modify(rs,nl,nr);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}

int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return sum[id];
	else{
		int m=(l+r)>>1;
		int ans=0;
		if(nl<=m)ans+=query(ls,nl,nr);
		if(m<nr)ans+=query(rs,nl,nr);
		return ans+off[id]*(r-l+1);
	}
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	n<<=1;
	for(int i=1;i<=n;++i)
		printf("%d ",queue[i]);
	puts("");
	char c[2];
	for(int i=0;i<m;++i){
		scanf("%s%d%d",c,&u,&v);
		if(*c=='P'){
			int lca=LCA(u,v);
			modify(1,n,1,b[lca],b[u]);
			modify(1,n,1,b[lca],b[v]);
		}
		else{
			if(d[u]>d[v])std::swap(u,v);
			printf("%d\n",query(1,n,1,b[u],e[v]));
		}
	}
	return 0;	
}

