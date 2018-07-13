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
int d[size],p[size],siz[size],son[size];
void DFS(int u){
	d[u]=d[p[u]]+1;
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			p[v]=u;
			DFS(v);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
}
int top[size],id[size],w[size],init[size],end[size],pcnt=0;
void buildChain(int u){
	++pcnt;
	id[u]=pcnt;
	init[pcnt]=w[u];
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
	end[u]=pcnt;
}
int P,sum[size<<2],off[size<<2]={};
void color(int l,int r,int id,int x){
	off[id]=(off[id]+x)%P;
	sum[id]=(sum[id]+(1LL*x*(r-l+1))%P)%P;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)sum[id]=init[l]%P;
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		sum[id]=(sum[id<<1]+sum[id<<1|1])%P;
	}
}
void push(int l,int r,int id){
	if(off[id]!=0){
		int m=(l+r)>>1;
		color(ls,off[id]);
		color(rs,off[id]);
		off[id]=0;
	}
}
int nl,nr,x;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(l,r,id,x);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		sum[id]=(sum[id<<1]+sum[id<<1|1])%P;
	}
}
void query(int l,int r,int id){
	if(nl<=l && r<=nr)x=(x+sum[id])%P;
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
typedef void(*Callable)(int l,int r,int id);
template<Callable func>
void apply(int u,int v){
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		nl=id[top[u]],nr=id[u];
		func(1,pcnt,1);
		u=p[top[u]];
	}
	nl=id[u],nr=id[v];
	if(nl>nr)std::swap(nl,nr);
	func(1,pcnt,1);
}
int main(){
	int n=read();
	int m=read();
	int root=read();
	P=read();
	for(int i=1;i<=n;++i)w[i]=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(root);
	top[root]=root;
	buildChain(root);
	build(1,n,1);
	for(int i=0;i<m;++i){
		switch(read()){
			case 1:{
				u=read();
				v=read();
				x=read();
				apply<modify>(u,v);
			}break;
			case 2:{
				u=read();
				v=read();
				x=0;
				apply<query>(u,v);
				print(x);
			}break;
			case 3:{
				u=read();
				x=read();
				nl=id[u],nr=end[u];
				modify(1,pcnt,1);
			}break;
			case 4:{
				u=read();
				x=0;
				nl=id[u],nr=end[u];
				query(1,pcnt,1);
				print(x);
			}break;
		}
	}
	return 0;
}

