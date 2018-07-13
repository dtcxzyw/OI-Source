#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
//'E' 'X' 'M'
int getOp(){
	int res,c;
	do c=getchar();
	while(c<'A'||c>'Z');
	while('A'<=c&&c<='Z'){
		res=c;
		c=getchar();
	}
	return res;
}
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	if(x<0)x=-x,putchar('-');
	printImpl(x);
	putchar('\n');
}
const int size=30001;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int d[size],p[size],siz[size],chi[size];
void DFS(int u){
	d[u]=d[p[u]]+1;
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			p[v]=u;
			DFS(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[chi[u]])
				chi[u]=v;
		}
	}
}
int id[size],w[size],pcnt=0,top[size];
void buildChain(int u){
	++pcnt;
	id[u]=pcnt;
	
	if(chi[u]){
		top[chi[u]]=top[u];
		buildChain(chi[u]);
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!id[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
int sum[size<<2],maxv[size<<2];
void update(int id){
	sum[id]=sum[id<<1]+sum[id<<1|1];
	maxv[id]=std::max(maxv[id<<1],maxv[id<<1|1]);
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)sum[id]=maxv[id]=w[l];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
void modify(int l,int r,int id,int u,int t){
	if(l==r)sum[id]=t,maxv[id]=t;
	else{
		int m=(l+r)>>1;
		if(u<=m)modify(ls,u,t);
		else modify(rs,u,t);
		update(id);
	}
}
int nl,nr,x;
void query1(int l,int r,int id){
	if(nl<=l && r<=nr)x=std::max(x,maxv[id]);
	else{
		int m=(l+r)>>1;
		if(nl<=m)query1(ls);
		if(m<nr)query1(rs);
	}
}
void query2(int l,int r,int id){
	if(nl<=l && r<=nr)x+=sum[id];
	else{
		int m=(l+r)>>1;
		if(nl<=m)query2(ls);
		if(m<nr)query2(rs);
	}
}
int n;
typedef void (*Callable)(int l,int r,int id);
template<Callable func>
void applyImpl(int u,int v){
	nl=id[u],nr=id[v];
	if(nl>nr)std::swap(nl,nr);
	func(1,n,1);
}
template<Callable func>
void apply(int u,int v){
	while(true){
		if(top[u]==top[v]){
			applyImpl<func>(u,v);
			return;
		}
		else{
			if(d[top[u]]<d[top[v]])std::swap(u,v);
			applyImpl<func>(u,top[u]);
			u=p[top[u]];
		}
	}
}
int main(){
	n=read();
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
	for(int i=1;i<=n;++i)
		w[id[i]]=read();
	build(1,n,1);
	int q=read(),op;
	for(int i=0;i<q;++i){
		op=getOp();
		u=read();
		v=read();
		if(op=='E')modify(1,n,1,id[u],v);
		else {
			if(op=='X'){
				x=-30000;
				apply<query1>(u,v);
			}
			else {
				x=0;
				apply<query2>(u,v);
			}
			print(x);
		}
	}
	return 0;
}

