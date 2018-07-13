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
const int size=1000005;
int fa[size];
int find(int u){
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[3*size];
bool flag[3*size]={};
struct EdgeG{
	int to,next,w;
} G[6*size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	G[cnt].to=v,G[cnt].next=last[u],G[cnt].w=w;
	last[u]=cnt;
}
int p[size],d[size]={},siz[size]={},son[size]={},len[size];
void buildTree(int u){
	siz[u]=1;
	for(int i=last[u];i;i=G[i].next){
		int v=G[i].to;
		if(!d[v]){
			d[v]=d[u]+1;
			p[v]=u;
			len[v]=G[i].w;
			buildTree(v);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
}
int id[size],val[size],top[size]={},icnt=0;
void buildChain(int u){
	id[u]=++icnt;
	val[icnt]=len[u];
	if(son[u]){
		top[son[u]]=top[u];
		buildChain(son[u]);
	}
	for(int i=last[u];i;i=G[i].next){
		int v=G[i].to;
		if(!top[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
struct Value{
	int fir,sec;
	Value(){}
	Value(int x):fir(x),sec(-1){}
	Value merge(int val) const{
		Value res=*this;
		if(val>res.fir)std::swap(res.fir,val);
		if(val<res.fir && val>res.sec)res.sec=val;
		return res;
	}
	Value merge(Value rhs) const{
		Value res=this->merge(rhs.fir);
		if(rhs.sec!=-1)res=res.merge(rhs.sec);
		return res;
	}
};
Value info[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)info[id]=Value(val[l]);
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		info[id]=info[id<<1].merge(info[id<<1|1]);
	}
}
int nl,nr;
Value query(int l,int r,int id){
	if(nl<=l && r<=nr)return info[id];
	else{
		int m=(l+r)>>1;
		Value res(-1);
		if(nl<=m)res=res.merge(query(ls));
		if(m<nr)res=res.merge(query(rs));
		return res;
	}
}
Value queryPath(int u,int v,int n){
	Value res(-1);
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		nl=id[top[u]],nr=id[u];
		res=res.merge(query(1,n,1));
		u=p[top[u]];
	}
	if(u!=v){
		if(d[u]>d[v])std::swap(u,v);
		nl=id[u]+1,nr=id[v];
		res=res.merge(query(1,n,1));
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		E[i].u=read();
		E[i].v=read();
		E[i].w=read();
	}	
	std::sort(E,E+m);
	int esiz=n-1;
	for(int i=1;i<=n;++i)fa[i]=i;
	long long minv=0;
	for(int i=0,j=0;i<m && j<esiz;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			flag[i]=true;
			addEdge(E[i].u,E[i].v,E[i].w);
			addEdge(E[i].v,E[i].u,E[i].w);
			minv+=E[i].w;
			++j;
		}
	}
	d[1]=1;
	buildTree(1);
	top[1]=1;
	buildChain(1);
	build(1,n,1);
	long long ans=1LL<<60;
	for(int i=0;i<m;++i)
		if(!flag[i]){
			Value val=queryPath(E[i].u,E[i].v,n);
			long long res=1LL<<60;
			if(val.fir!=E[i].w)res=minv-val.fir+E[i].w;
			else if(val.sec!=-1)res=minv-val.sec+E[i].w;
			ans=std::min(ans,res);
		}
	printf("%lld\n",ans);
	return 0;
}

