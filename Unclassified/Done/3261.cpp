#include <cstdio>
#include <algorithm>
long long read(){
	long long res=0;
	int c;
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
const int size=301000;
struct Node{
	int l,r,dis;
	long long key,mul,add;
} T[size];
void color(int x,long long mul,long long add){
	if(x){
		T[x].key=T[x].key*mul+add;
		T[x].add=T[x].add*mul+add;
		T[x].mul*=mul;
	}
}
void push(int x){
	if(T[x].mul!=1 || T[x].add){
		color(T[x].l,T[x].mul,T[x].add);
		color(T[x].r,T[x].mul,T[x].add);
		T[x].mul=1,T[x].add=0;
	}
}
int merge(int x,int y){
	if(!x || !y)return x|y;
	if(T[x].key>T[y].key)std::swap(x,y);
	push(x);
	T[x].r=merge(T[x].r,y);
	if(T[T[x].l].dis<T[T[x].r].dis)std::swap(T[x].l,T[x].r);
	T[x].dis=T[T[x].r].dis+1;
	return x;
}
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
long long h[size],v[size];
int a[size],ccnt[size]={},end[size]={},d[size],c[size],root[size]={};
void DFS(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		d[v]=d[u]+1;
		DFS(v);
		root[u]=merge(root[u],root[v]);
	}
	while(root[u] && T[root[u]].key<h[u]){
		++ccnt[u];
		push(root[u]);
		end[root[u]]=u;
		root[u]=merge(T[root[u]].l,T[root[u]].r);
	}
	if(a[u])color(root[u],v[u],0);
	else color(root[u],1,v[u]);
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)h[i]=read();
	for(int i=2;i<=n;++i){
		addEdge(read(),i);
		a[i]=read();
		v[i]=read();
	}
	for(int i=1;i<=n;++i){
		T[i].add=0,T[i].mul=1,T[i].key=read(),T[i].dis=0;
		c[i]=read();
		root[c[i]]=merge(root[c[i]],i);
	}
	d[0]=0,d[1]=1;
	DFS(1);
	for(int i=1;i<=n;++i)printf("%d\n",ccnt[i]);
	for(int i=1;i<=m;++i)printf("%d\n",d[c[i]]-d[end[i]]);
	return 0;
}

