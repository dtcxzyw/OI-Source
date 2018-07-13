#include <cstdio>
#include <algorithm>
const int size=16001;
struct Edge{
	int to,next;
} E[size<<1];
int last[size]={},cnt=0,w[size],ans=-2147483647;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int DFS(int x,int p){
	int res=w[x];
	for(int i=last[x];i;i=E[i].next)
		if(E[i].to!=p)
			res+=std::max(0,DFS(E[i].to,x));
	ans=std::max(ans,res);
	return res;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&w[i]);
	int u,v;
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	printf("%d\n",ans);
	return 0;
}

