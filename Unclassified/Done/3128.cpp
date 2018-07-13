#include <cstdio>
#include <algorithm>
const int size=50001;
struct Edge{
	int to,next;
} E[size<<1];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}

int siz[size],child[size]={},top[size],p[size],id[size],d[size];
void buildTree(int x){
	siz[x]=1;
	d[x]=d[p[x]]+1;
	for(int i=last[x];i;i=E[i].next){
		int v=E[i].to;
		if(p[x]!=v){
			p[v]=x;
			buildTree(v);
			siz[x]+=siz[v];
			if(siz[child[x]]<siz[v])child[x]=v;
		}
	}
}
int pcnt=0;
void buildChain(int x){
	id[x]=++pcnt;
	if(child[x]){
		top[child[x]]=top[x];
		buildChain(child[x]);
	}
	for(int i=last[x];i;i=E[i].next){
		int v=E[i].to;
		if(p[x]!=v && child[x]!=v){
			top[v]=v;
			buildChain(v);
		}	
	}
}

int maxv[size<<2|1]={},off[size<<2|1]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1 
void modify(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)++off[id],++maxv[id];
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr);
		if(m<nr)modify(rs,nl,nr);
		maxv[id]=std::max(maxv[id<<1],maxv[id<<1|1])+off[id];
	}
}
void modify(int u,int v,int n){
	u=id[u],v=id[v];
	if(u>v)std::swap(u,v);
	modify(1,n,1,u,v);
}
void add(int u,int v,int n){
	while(true){
		if(top[u]==top[v]){
			modify(u,v,n);
			break;
		}
		else{
			if(d[top[u]]<d[top[v]])std::swap(u,v);
			modify(u,top[u],n);
			u=p[top[u]];
		}
	}
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n,k;
	n=read();
	k=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	buildTree(1);
	top[1]=1;
	buildChain(1);
	for(int i=0;i<k;++i){
		u=read();
		v=read();
		add(u,v,n);
	}
	printf("%d\n",maxv[1]);
	return 0;
}

