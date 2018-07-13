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
	while(c!='Q' && c!='C');
	return c;
}
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
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
int p[size],d[size]={},son[size],siz[size];
void DFS(int u){
	siz[u]=1;
	d[u]=d[p[u]]+1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			p[v]=u;
			DFS(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
}
int top[size]={},id[size],vert[size],pcnt=0;
void buildChain(int u){
	id[u]=++pcnt;
	vert[id[u]]=u;
	if(son[u]){
		top[son[u]]=top[u];
		buildChain(son[u]);
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!top[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
int c[size],mark[size<<2]={};
struct Info{
	int lc,rc,midc;
	int size(){
		if(midc==0)return 1+(lc!=rc);
		return midc+2;
	}
} tree[size<<2];
Info merge(Info lhs,Info rhs){
	if(rhs.midc==-1)return lhs;
	if(lhs.midc==-1)return rhs;
	Info res;
	res.lc=lhs.lc,res.rc=rhs.rc;
	if(lhs.size()==1 && rhs.size()==1)res.midc=0;
	else if(lhs.size()==1)res.midc=rhs.midc+(lhs.rc!=rhs.lc);
	else if(rhs.size()==1)res.midc=lhs.midc+(lhs.rc!=rhs.lc);
	else res.midc=lhs.midc+rhs.midc+1+(lhs.rc!=rhs.lc);
	//printf("(%d %d %d)^(%d %d %d)=(%d %d %d)\n",lhs.lc,lhs.rc,lhs.midc,rhs.lc,rhs.rc,rhs.midc,res.lc,res.rc,res.midc);
	return res;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int id){
	tree[id]=merge(tree[id<<1],tree[id<<1|1]);
}
void build(int l,int r,int id){
	if(l==r)tree[id].lc=tree[id].rc=c[vert[l]],tree[id].midc=0;
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
void color(int id,int col){
	mark[id]=col;
	tree[id].lc=tree[id].rc=col;
	tree[id].midc=0;
}
void push(int id){
	if(mark[id]){
		color(id<<1,mark[id]);
		color(id<<1|1,mark[id]);
		mark[id]=0;
	}
}
int nl,nr,col;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(id,col);
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		update(id);
	}
}
Info query(int l,int r,int id){
	if(nl<=l && r<=nr)return tree[id];
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m && m<nr)return merge(query(ls),query(rs));
		else if(nl<=m)return query(ls);
		else return query(rs);
	}
}
void change(int u,int v,int n){
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		nl=id[top[u]],nr=id[u];
		modify(1,n,1);
		u=p[top[u]];
	}
	nl=id[u],nr=id[v];
	if(nl>nr)std::swap(nl,nr);
	modify(1,n,1);
}
int slove(int u,int v,int n){
	Info iu,iv;
	iu.midc=iv.midc=-1;
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v),std::swap(iu,iv);
		nl=id[top[u]],nr=id[u];
		iu=merge(query(1,n,1),iu);
		u=p[top[u]];
	}
	nl=id[u],nr=id[v];
	if(nl>nr)std::swap(nl,nr),std::swap(iu,iv);
	Info m=query(1,n,1);
	std::swap(iu.lc,iu.rc);
	Info res=merge(merge(iu,m),iv);
	return res.size();
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)c[i]=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	top[1]=1;
	buildChain(1);
	build(1,n,1);
	for(int i=0;i<m;++i)
		if(getOp()=='C'){
			u=read();
			v=read();
			col=read();
			change(u,v,n);
		}
		else print(slove(read(),read(),n));
	return 0;
}

