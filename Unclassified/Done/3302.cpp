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
int getOp(){
	int c;
	do c=getchar();
	while(c!='Q' && c!='L');
	return c;
}
const int size=100005;
struct Edge{
	int to,next;
} E[size*4];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
struct Seg{
	int l,r,siz;
} T[size*101];
int ncnt=0;
void add(int l,int r,int& id,int p){
	T[ncnt+1]=T[id];
	id=++ncnt;
	++T[id].siz;
	if(l!=r){
		int m=(l+r)>>1;
		if(p<=m)add(l,m,T[id].l,p);
		else add(m+1,r,T[id].r,p);
	}
}
int d[size]={},p[size][20],root[size],A[size],siz;
void DFS(int u,int f){
	d[u]=d[f]+1;
	for(int i=1;i<20;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	root[u]=root[f];
	add(1,siz,root[u],A[u]);	
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=f){
			p[v][0]=u;
			DFS(v,u);
		}
	}
}
int lca(int u,int v){
	if(d[u]<d[v])std::swap(u,v);
	int delta=d[u]-d[v];
	for(int i=0;i<20;++i)
		if(delta&(1<<i))
			u=p[u][i];
	for(int i=19;i>=0;--i)
		if(p[u][i]!=p[v][i])
			u=p[u][i],v=p[v][i];
	return u==v?u:p[u][0];
}
int lval(int id){
	return T[T[id].l].siz;
}
int query(int l,int r,int a,int b,int c,int d,int k){
	if(l==r)return l;
	else{
		int m=(l+r)>>1;
		int lsiz=lval(a)+lval(b)-lval(c)-lval(d);
		if(k<=lsiz)return query(l,m,T[a].l,T[b].l,T[c].l,T[d].l,k);
		return query(m+1,r,T[a].r,T[b].r,T[c].r,T[d].r,k-lsiz);
	}
}
int fa[size],tsiz[size];
int find(int u){
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
int B[size];
void mergeBlock(int u,int v){
	fa[v]=u;
	tsiz[u]+=tsiz[v];
}
void foo(){
	int n=read();
	int m=read();
	int t=read();
	for(int i=1;i<=n;++i)A[i]=read();
	memcpy(B,A,sizeof(B));
	std::sort(B+1,B+n+1);
	siz=std::unique(B+1,B+n+1)-B-1;
	for(int i=1;i<=n;++i)
		A[i]=std::lower_bound(B+1,B+siz+1,A[i])-B;
	for(int i=1;i<=n;++i)fa[i]=i,tsiz[i]=1;
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
		mergeBlock(find(u),find(v));
	}
	for(int i=1;i<=n;++i)
		if(!d[i])
			DFS(find(i),0);
	int lastAns=0;
	for(int i=0;i<t;++i){
		int op=getOp();
		int u=read()^lastAns;
		int v=read()^lastAns;
		if(op=='Q'){
			int k=read()^lastAns;
			int plca=lca(u,v),flca=p[plca][0];
			int pos=query(1,siz,root[u],root[v],root[plca],root[flca],k);
			printf("%d\n",B[pos]);
			lastAns=B[pos];
		}
		else{
			addEdge(u,v);
			addEdge(v,u);
			int fu=find(u),fv=find(v);
			if(tsiz[fu]<tsiz[fv])std::swap(fu,fv),std::swap(u,v);
			mergeBlock(fu,fv);
			p[v][0]=u;
			DFS(v,u);
		}
	}
}
int main(){
	int t=read();
	foo();
	return 0;
}

