#include <cstdio>
#include <algorithm>
#include <cstring>
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
const int size=100005;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],d[size]={},son[size]={},siz[size]={};
void buildTree(int u){
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			p[v]=u;
			d[v]=d[u]+1;
			buildTree(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
	}
}
int id[size],map[size],icnt=0,top[size]={};
void buildChain(int u){
	id[u]=++icnt;
	map[id[u]]=u;
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
	int l,r,val;
} T[size*20];
int pos,ncnt=0;
void modify(int l,int r,int& id){
	T[ncnt+1]=T[id];
	id=++ncnt;
	++T[id].val;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)modify(l,m,T[id].l);
		else modify(m+1,r,T[id].r);
	}
}
int query(int l,int r,int a,int b){
	if(r<=pos)return T[a].val-T[b].val;
	else{
		int m=(l+r)>>1;
		int res=query(l,m,T[a].l,T[b].l);
		if(pos>m)res+=query(m+1,r,T[a].r,T[b].r);
		return res;
	}
}
int range[size][2],root[size];
int query(int siz,int n){
	if(pos==0)return 0;
	int res=0;
	for(int i=0;i<siz;++i)
		res+=query(1,n,root[range[i][1]],root[range[i][0]-1]);
	return res;	
}
int queryPath(int u,int v,int k,int n){
	int cnt=0;
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);	
		range[cnt][0]=id[top[u]];
		range[cnt][1]=id[u];
		u=p[top[u]];
		++cnt;
	}
	if(d[u]>d[v])std::swap(u,v);
	range[cnt][0]=id[u];
	range[cnt][1]=id[v];
	++cnt;
	int l=1,r=n,ans=1;
	while(l<=r){
		int m=(l+r)>>1;
		pos=m-1;
		if(query(cnt,n)<k)l=m+1,ans=m;
		else r=m-1;
	}
	return ans;
}
int A[size],B[size];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)A[i]=read();
	memcpy(B,A,sizeof(A));
	std::sort(B+1,B+n+1);
	int siz=std::unique(B+1,B+n+1)-B-1;
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=1;
	buildTree(1);
	top[1]=1;
	buildChain(1);
	for(int i=1;i<=n;++i){
		root[i]=root[i-1];
		pos=std::lower_bound(B+1,B+siz+1,A[map[i]])-B;
		modify(1,siz,root[i]);
	}
	int ans=0;
	for(int i=0;i<m;++i){
		int u=read()^ans;
		int v=read();
		int k=read();
		ans=B[queryPath(u,v,k,siz)];
		printf("%d\n",ans);
	}
	return 0;
}

