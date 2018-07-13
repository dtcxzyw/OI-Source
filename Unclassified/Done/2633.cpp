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
const int size=100005;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size][18],d[size]={};
struct Seg{
	int l,r,val;
} T[size*20];
int pos,ncnt=0;
void modify(int l,int r,int& id){
	T[ncnt+1]=T[id];
	id=++ncnt;
	++T[id].val;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)modify(l,m,T[id].l);
		else modify(m+1,r,T[id].r);
	}
}
int lval(int u){
	return T[T[u].l].val;
}
int query(int l,int r,int a,int b,int c,int d){
	if(l==r)return l;
	else{
		int m=(l+r)>>1;
		int ls=lval(a)+lval(b)-lval(c)-lval(d);
		if(ls>=pos)return query(l,m,T[a].l,T[b].l,T[c].l,T[d].l);
		pos-=ls;
		return query(m+1,r,T[a].r,T[b].r,T[c].r,T[d].r);
	}
}
int lca(int u,int v){
	if(d[u]<d[v])std::swap(u,v);
	int delta=d[u]-d[v];
	for(int i=0;i<18;++i)
		if(delta&(1<<i))
			u=p[u][i];
	for(int i=17;i>=0;--i)
		if(p[u][i]!=p[v][i])
			u=p[u][i],v=p[v][i];
	return u==v?u:p[u][0];
}
int A[size],B[size],root[size],siz;
void DFS(int u){
	pos=std::lower_bound(B+1,B+siz+1,A[u])-B;
	modify(1,siz,root[u]);
	for(int i=1;i<18;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			p[v][0]=u;
			d[v]=d[u]+1;
			root[v]=root[u];
			DFS(v);
		}
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)A[i]=read();
	memcpy(B,A,sizeof(A));
	std::sort(B+1,B+n+1);
	siz=std::unique(B+1,B+n+1)-B-1;
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=1;
	DFS(1);
	int ans=0;
	for(int i=0;i<m;++i){
		int u=read()^ans;
		int v=read();
		pos=read();
		int lcap=lca(u,v);
		ans=B[query(1,siz,root[u],root[v],root[lcap],root[p[lcap][0]])];
		printf("%d\n",ans);
	}
	return 0;
}

