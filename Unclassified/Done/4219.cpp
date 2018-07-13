#include <cstdio>
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
	while(c!='A' && c!='Q');
	return c;
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
struct Seg{
	int l,r,siz;
} T[size*20];
int icnt=0;
int build(int l,int r,int p){
	int id=++icnt;
	T[id].siz=1;
	if(l!=r){
		int m=(l+r)>>1;
		if(p<=m)T[id].l=build(l,m,p);
		else T[id].r=build(m+1,r,p);
	}
	return id;
}
int merge(int u,int v){
	if(u&&v){
		T[u].siz+=T[v].siz;
		T[u].l=merge(T[u].l,T[v].l);
		T[u].r=merge(T[u].r,T[v].r);
		return u;
	}
	return u|v;
}
int query(int l,int r,int id,int nl,int nr){
	if(id){
		if(nl<=l && r<=nr)return T[id].siz;
		else{
			int m=(l+r)>>1,res=0;
			if(nl<=m)res+=query(l,m,T[id].l,nl,nr);
			if(m<nr)res+=query(m+1,r,T[id].r,nl,nr);
			return res;
		}	
	}
	return 0;
}
int n,ncnt=0,d[size]={},L[size],R[size],root[size]={};
void DFS(int u){
	L[u]=++ncnt;
	root[u]=build(1,n,L[u]);
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			d[v]=d[u]+1;
			DFS(v);
		}
	}
	R[u]=ncnt;
}
int fa[size];
int find(int u){
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
struct Operator{
	int op,u,v;
} op[size];
int main(){
	n=read();
	int q=read();
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=0;i<q;++i){
		op[i].op=getOp();
		op[i].u=read();
		op[i].v=read();
		if(op[i].op=='A'){
			addEdge(op[i].u,op[i].v);
			addEdge(op[i].v,op[i].u);
		}
	}
	for(int i=1;i<=n;++i)
		if(!d[i]){
			d[i]=1;
			DFS(i);
		}
	for(int i=0;i<q;++i)
		if(op[i].op=='A'){
			int fu=find(op[i].u),fv=find(op[i].v);
			if(d[fu]>d[fv])std::swap(fu,fv);
			root[fu]=merge(root[fu],root[fv]);
			fa[fv]=fu;
		}
		else{
			int u=op[i].u,v=op[i].v;
			if(d[u]<d[v])std::swap(u,v);
			int fu=find(u);
			long long sizu=query(1,n,root[fu],L[u],R[u]);
			long long sizv=T[root[fu]].siz-sizu;
			printf("%lld\n",sizu*sizv);
		}
	return 0;
}

