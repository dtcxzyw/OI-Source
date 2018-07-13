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
const int size=300005;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int id[size],map[size],siz[size],d[size]={},icnt=0;
void DFS(int u){
	siz[u]=1;
	id[u]=++icnt;
	map[icnt]=u;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			d[v]=d[u]+1;
			DFS(v);
			siz[u]+=siz[v];
		}
	}
}
struct Seg{
	int l,r;
	long long sum;
} T[size*20];
int pos,val,ncnt=0;
void insert(int l,int r,int& id){
	T[++ncnt]=T[id];
	id=ncnt;
	T[id].sum+=val;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)insert(l,m,T[id].l);
		else insert(m+1,r,T[id].r);
	}
}
int nl,nr;
long long query(int l,int r,int a,int b){
	long long delta=T[a].sum-T[b].sum;
	if(nl<=l && r<=nr)return delta;
	if(delta){
		int m=(l+r)>>1;
		long long res=0;
		if(nl<=m)res+=query(l,m,T[a].l,T[b].l);
		if(m<nr)res+=query(m+1,r,T[a].r,T[b].r);
		return res;
	}
	return 0;
}
int root[size]={};
int minv(int a,int b){
	return a<b?a:b;
}
int main(){
	int n=read();
	int q=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=1;
	DFS(1);
	int maxd=0;
	for(int i=1;i<=n;++i)
		if(d[i]>maxd)
			maxd=d[i];
	for(int i=1;i<=n;++i){
		root[i]=root[i-1];
		int u=map[i];
		pos=d[u];
		val=siz[u]-1;
		insert(1,maxd,root[i]);
	}
	for(int i=0;i<q;++i){
		int p=read();
		int k=read();
		int base=id[p],psiz=siz[p],pd=d[p];
		int a=root[base+psiz-1],b=root[base];
		nl=pd+1,nr=pd+k;
		long long res=query(1,maxd,a,b);
		res+=static_cast<long long>(psiz-1)*minv(pd-1,k);
		printf("%lld\n",res);
	}
	return 0;
}

