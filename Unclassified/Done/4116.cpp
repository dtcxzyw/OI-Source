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
const int size=100100;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],siz[size]={},son[size]={};
void buildTree(int u){
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v){
			p[v]=u;
			buildTree(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
	}
}
int map[size],pid[size],top[size]={},icnt=0;
void buildChain(int u){
	map[u]=++icnt;
	pid[icnt]=u;
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
int sum[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int x){
	if(l==r)sum[id]^=1;
	else{
		int m=(l+r)>>1;
		if(x<=m)modify(ls,x);
		else modify(rs,x);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
int queryFull(int l,int r,int id){
	if(l==r)return pid[l];
	int m=(l+r)>>1;
	if(sum[id<<1])return queryFull(ls);
	return queryFull(rs);
}
int query(int l,int r,int id,int nl,int nr){
	if(sum[id]==0)return -1;
	if(nl<=l && r<=nr)return queryFull(l,r,id);
	else{
		int m=(l+r)>>1;
		if(nl<=m){
			int res=query(ls,nl,nr);
			if(res!=-1)return res;
		}
		if(m<nr){
			int res=query(rs,nl,nr);
			if(res!=-1)return res;
		}
		return -1;
	}
}
int n;
int query(int u){
	if(u==0)return -1;
	int res=query(p[top[u]]);
	if(res!=-1)return res;
	return query(1,n,1,map[top[u]],map[u]);
}
int main(){
	n=read();
	int q=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	buildTree(1);
	top[1]=1;
	buildChain(1);
	for(int i=0;i<q;++i)
		if(read())printf("%d\n",query(read()));
		else modify(1,n,1,map[read()]);
	return 0;
}

