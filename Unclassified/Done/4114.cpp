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
	while(c<'A'||c>'Z');
	return c;
}
const int size=100100;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=1;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int p[size],siz[size],d[size],son[size]={},w[size],pid[size];
void buildTree(int u){
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v){
			p[v]=u;
			d[v]=d[u]+1;
			w[v]=E[i].w;
			pid[i>>1]=v;
			buildTree(v);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
}
int top[size]={},id[size]={},map[size],icnt=0;
void buildChain(int u){
	id[u]=++icnt;
	map[icnt]=u;
	if(son[u]){
		top[son[u]]=top[u];
		buildChain(son[u]);
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!id[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
int val[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)val[id]=w[map[l]];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		val[id]=std::max(val[id<<1],val[id<<1|1]);
	}
}
int k,t;
void modify(int l,int r,int id){
	if(l==r)val[id]=t;
	else{
		int m=(l+r)>>1;
		if(k<=m)modify(ls);
		else modify(rs);
		val[id]=std::max(val[id<<1],val[id<<1|1]);
	}
}
int nl,nr,ans;
void query(int l,int r,int id){
	if(nl<=l && r<=nr)ans=std::max(ans,val[id]);
	else{
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
void queryPath(int u,int v,int n){
	ans=0;
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		nl=id[top[u]],nr=id[u];
		query(1,n,1);
		u=p[top[u]];
	}
	if(u!=v){
		if(d[u]<d[v])std::swap(u,v);
		nl=id[v]+1,nr=id[u];
		query(1,n,1);	
	}
}
int main(){
	int n=read();
	for(int i=2;i<=n;++i){
		int u=read();
		int v=read();
		int w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	siz[0]=p[1]=d[1]=0;
	buildTree(1);
	top[1]=1;
	buildChain(1);
	build(1,n,1);
	while(true){
		int op=getOp();
		if(op=='C'){
			k=id[pid[read()]];
			t=read();
			modify(1,n,1);
		}
		else if(op=='Q'){
			queryPath(read(),read(),n);
			printf("%d\n",ans);
		}
		else break;
	}
	return 0;
}

