#include <cstdio>
#include <algorithm>
const int size=300001;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],d[size],siz[size]={};
void build(int x){
	d[x]=d[p[x]]+1;
	for(int i=last[x];i;i=E[i].next)
		if(p[x]!=E[i].to){
			p[E[i].to]=x;
			build(E[i].to);
			siz[x]+=siz[E[i].to]+1;
		}
}
long long res;
void DFS(int a,int k){
	if(k)
		for(int i=last[a];i;i=E[i].next)
			if(E[i].to!=p[a]){
				DFS(E[i].to,k-1);
				res+=siz[E[i].to];
			}
}
void query(int a,int k){
	res=1LL*std::min(d[a]-1,k)*siz[a];//parents
	DFS(a,k);//children
}
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	int u,v;
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	build(1);
	int a,k;
	for(int i=0;i<q;++i){
		scanf("%d%d",&a,&k);
		query(a,k);
		printf("%lld\n",res);
	}
	return 0;	
}

