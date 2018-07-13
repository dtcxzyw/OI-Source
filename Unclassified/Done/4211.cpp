#include <cstdio>
#include <vector>
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
const int size=50005,mod=201314;
struct Edge{
	int to,next;
} E[size];
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
		buildTree(v);
		siz[u]+=siz[v];
		if(!son[u] || siz[son[u]]<siz[v])son[u]=v;
	}
}
int top[size],id[size]={},icnt=0;
void buildChain(int u){
	id[u]=++icnt;
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
long long sum[size<<2]={},lazy[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void color(int l,int r,int id,long long val){
	sum[id]+=val*(r-l+1);
	lazy[id]+=val;
}
void push(int l,int r,int m,int id){
	if(lazy[id]){
		color(ls,lazy[id]);
		color(rs,lazy[id]);
		lazy[id]=0;
	}
}
int nl,nr;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(l,r,id,1);
	else{
		int m=(l+r)>>1;
		push(l,r,m,id);
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
long long res;
void query(int l,int r,int id){
	if(nl<=l && r<=nr)res+=sum[id];
	else{
		int m=(l+r)>>1;
		push(l,r,m,id);
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
typedef void (*Func)(int,int,int);
template<Func func>
void apply(int u,int siz){
	while(u!=-1){
		nl=id[top[u]];
		nr=id[u];
		func(1,siz,1);
		u=p[top[u]];
	}
}
int pos[size];
std::vector<int> add[size],sub[size];
long long ans[size]={};
int main(){
	int n=read();
	int q=read();
	for(int i=1;i<n;++i){
		p[i]=read();
		addEdge(p[i],i);
	}
	p[0]=-1;
	buildTree(0);
	top[0]=0;
	buildChain(0);
	for(int i=0;i<q;++i){
		int l=read();
		int r=read();
		pos[i]=read();
		if(l)sub[l-1].push_back(i);
		add[r].push_back(i);
	}
	for(int i=0;i<n;++i){
		apply<modify>(i,n);
		for(int j=0;j<add[i].size();++j){
			res=0;
			int u=add[i][j];
			apply<query>(pos[u],n);
			ans[u]+=res;
		}
		for(int j=0;j<sub[i].size();++j){
			res=0;
			int u=sub[i][j];
			apply<query>(pos[u],n);
			ans[u]-=res;
		}
	}
	for(int i=0;i<q;++i)
		printf("%d\n",static_cast<int>(ans[i]%mod));
	return 0;
}

