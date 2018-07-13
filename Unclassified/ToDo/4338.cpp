#include <cstdio>
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
const int size=400005;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
long long At[size]={},Am[size],val[size]={},res=0;
int p[size],son[size]={},h[size],siz[size]={};
bool isReal[size]={};
void buildTree(int u){
	h[u]=u;
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v){
			p[v]=u;
			buildTree(v);
			At[u]+=At[v];
			if(Am[u]<At[v])
				Am[u]=At[v],h[u]=v;
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	if((Am[u]<<1)>=At[u]+1){
		val[u]=(At[u]-Am[u])<<1;
		if(h[u]!=u)isReal[u]=true;
	}
	else val[u]=At[u]-1;
	res+=val[u];
}
int top[size],id[size]={},map[size],icnt=0;
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
int rcnt[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)rcnt[id]=isReal[map[id]];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		rcnt[id]=rcnt[id<<1]+rcnt[id<<1|1];
	}
}
void modify(int l,int r,int id,int pos,int op){
	rcnt[id]+=op;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)modify(ls);
		else modify(rs);
	}
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr){
		
	}
	else{
		
	}
}
void updateReal(int u,int x,int n){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p[u]){
			int now=v==x;
			modify(1,n,1,id[v],now-isReal[v]);
			isReal[v]=now;
		}
	}
}
void update(int u){
	
}
void updateChain(int u){
	
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)At[i]=read();
	memcpy(Am+1,At+1,n*sizeof(long long));
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	p[1]=0;
	buildTree(1);
	top[1]=1;
	buildChain(1);
	build(1,n,1);
	printf("%lld\n",res);
	for(int i=0;i<m;++i){
		int x=read();
		int w=read();
			
	}
	return 0;
}

