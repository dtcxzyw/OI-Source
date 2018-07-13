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
int getCode(){
	int c;
	do c=getchar();
	while(c!='A' && c!='Q');
	return c;
}
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	printImpl(x);
	putchar('\n');
}
const int size=100010;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],d[size],siz[size],son[size]={};
void DFS(int u){
	siz[u]=1;
	int maxv=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		p[v]=u;
		d[v]=d[u]+1;
		DFS(v);
		siz[u]+=siz[v];
		if(siz[v]>maxv)son[u]=v,maxv=siz[v];
	}
}
int top[size],id[size]={},pcnt=0; 
void buildChain(int u){
	id[u]=++pcnt;
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
long long sum[size<<2]={},off[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void color(int l,int r,int id,long long x){
	off[id]+=x;
	sum[id]+=x*(r-l+1);
}
void push(int l,int r,int id){
	if(off[id]){
		int m=(l+r)>>1;
		color(ls,off[id]);
		color(rs,off[id]);
		off[id]=0;
	}
}
int nl,nr;
long long x;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(l,r,id,x);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
void query(int l,int r,int id){
	if(nl<=l && r<=nr)x+=sum[id];
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
void addChain(int u,int v,int n){
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
int main(){
	int n=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
	}
	DFS(0);
	top[0]=0;
	buildChain(0);
	int q=read();
	for(int i=0;i<q;++i)
		if(getCode()=='A'){
			u=read();
			v=read();
			x=read();
			addChain(u,v,n);
		}
		else{
			u=read();
			nl=id[u],nr=id[u]+siz[u]-1,x=0;
			query(1,n,1);
			print(x);
		}
	return 0;
}

