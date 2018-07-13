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
	while(c!='P' && c!='Q');
	return c;
}
const int size=100010;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
bool flag[size]={};
int p[size][18]={},dep[size]={},l[size],r[size],pcnt=0;
void DFS(int u){
	flag[u]=true;
	dep[u]=dep[p[u][0]]+1;
	for(int i=1;i<18;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	l[u]=++pcnt;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			p[v][0]=u;
			DFS(v);
		}
	}
	r[u]=++pcnt;
}
int query(int u,int v){
	if(dep[u]>dep[v])std::swap(u,v);
	int d=dep[v]-dep[u];
	for(int i=0;i<18;++i)
		if(d&(1<<i))v=p[v][i];
	for(int i=17;i>=0;--i)
		if(p[u][i]!=p[v][i])
			u=p[u][i],v=p[v][i];
	return u==v?u:p[u][0];
}
int A[size*2];
void add(int i,int n,int v){
	while(i<=n){
		A[i]+=v;
		i+=i&-i;
	}
}
int query(int i){
	int res=0;
	while(i){
		res+=A[i];
		i-=i&-i;
	}
	return res;
}
int main(){
	int n,m;
	n=read();
	m=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	n<<=1;
	for(int i=0;i<m;++i){
		int c=getCode();
		u=read();
		v=read();
		if(c=='P'){
			int lca=query(u,v);
			add(l[u],n,1);
			add(l[v],n,1);
			add(l[lca],n,-2);
		}
		else{
			if(dep[u]<dep[v])std::swap(u,v);
			printf("%d\n",query(r[u])-query(l[u]-1));
		}
	}
	return 0;
}

