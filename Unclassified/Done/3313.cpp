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
const int size=100005,maxc=10005;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],d[size]={},siz[size]={},son[size]={};
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
int id[size],icnt=0,top[size]={};
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
	int l,r,maxv,sum;
} T[size*21];
#define ls l,m,T[id].l
#define rs m+1,r,T[id].r
int pos,val,ncnt=0;
void modify(int l,int r,int& id){
	if(!id)id=++ncnt;
	if(l==r)T[id].maxv=T[id].sum=val;
	else{
		int m=(l+r)>>1;
		if(pos<=m)modify(ls);
		else modify(rs);
		T[id].maxv=std::max(T[T[id].l].maxv,T[T[id].r].maxv);
		T[id].sum=T[T[id].l].sum+T[T[id].r].sum;
	}
}
int root[maxc],A[size],C[size];
void update(int u,int v,int n){
	pos=id[u];
	val=v;
	modify(1,n,root[C[u]]);
}
int res,nl,nr;
typedef void (*Func)(int id);
void applyMaxv(int id){
	res=std::max(res,T[id].maxv);
}
void applySum(int id){
	res+=T[id].sum;
}
template<Func func>
void query(int l,int r,int id){
	if(id){
		if(nl<=l && r<=nr)func(id);
		else{
			int m=(l+r)>>1;
			if(nl<=m)query<func>(ls);
			if(m<nr)query<func>(rs);
		}
	}
}
template<Func func>
void queryChain(int u,int v,int n,int rt){
	nl=id[u],nr=id[v];
	query<func>(1,n,rt);
}
template<Func func>
void queryPath(int u,int v,int n,int rt){
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		queryChain<func>(top[u],u,n,rt);
		u=p[top[u]];
	}
	if(d[u]>d[v])std::swap(u,v);
	queryChain<func>(u,v,n,rt);
}
int main(){
	int n=read();
	int q=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		C[i]=read();
	}
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
		pos=id[i];
		val=A[i];
		modify(1,n,root[C[i]]);
	}
	for(int i=0;i<q;++i)
		if(getOp()=='C'){
			if(getOp()=='C'){
				int u=read();
				update(u,0,n);
				C[u]=read();
				update(u,A[u],n);
			}
			else{
				int u=read();
				A[u]=read();
				update(u,A[u],n);
			}
		}
		else{
			res=0;
			int op=getOp();
			int u=read();
			int v=read();
			int rt=root[C[u]];
			if(op=='S')queryPath<applySum>(u,v,n,rt);
			else queryPath<applyMaxv>(u,v,n,rt);
			printf("%d\n",res);
		}
	return 0;
}

