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
const int size=200005;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],d[size]={},siz[size],son[size]={};
void buildTree(int u){
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			d[v]=d[u]+1;
			p[v]=u;
			buildTree(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
	}
}
int top[size]={},id[size],icnt=0;
void buildChain(int u){
	id[u]=++icnt;
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
struct Seg{
	int l,r,sum;
} T[size*20];
int root[size],ncnt=0;
#define ls l,m,T[id].l
#define rs m+1,r,T[id].r
void modify(int l,int r,int& id,int p){
	T[ncnt+1]=T[id];
	id=++ncnt;
	++T[id].sum;
	if(l!=r){
		int m=(l+r)>>1;
		if(p<=m)modify(ls,p);
		else modify(rs,p);
	}
}
int nl,nr;
int query(int l,int r,int id){
	if(nl<=l && r<=nr)return T[id].sum;
	else if(T[id].sum){
		int m=(l+r)>>1,res=0;
		if(nl<=m)res+=query(ls);
		if(m<nr)res+=query(rs);
		return res;
	}	
}
int queryChain(int fu,int u,int n,int rt){
	if(rt){
		nl=id[fu];
		nr=id[u];
		return query(1,n,rt);
	}
	return 0;
}
void queryPath(int u,int v,int rt,int n){
	int s=u,t=v,ans=0;
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		ans+=queryChain(top[u],u,n,rt);
		u=p[top[u]];
	}
	if(d[u]<d[v])std::swap(u,v);
	int lca=v;
	ans+=queryChain(v,u,n,rt);
	int sum=d[s]+d[t]-(d[lca]<<1)+1;
	printf("%d %d\n",sum,ans);
}
int t[size]={};
int main(){
	int n=read();
	int rt;
	for(int i=1;i<=n;++i){
		int p=read();
		if(p)addEdge(p,i);
		else rt=i;
	}
	d[rt]=1;
	buildTree(rt);
	top[rt]=rt;
	buildChain(rt);
	int q=read();
	for(int i=1;i<=q;++i){
		root[i]=root[i-1];
		if(read()==1){
			int u=read();
			int v=read();
			int t=i-read()-1;
			queryPath(u,v,t>0?root[t]:0,n);
		}
		else{
			int x=read();
			if(!t[x]){
				modify(1,n,root[i],id[x]);
				t[x]=i;
			}
		}
	}
	return 0;
}

