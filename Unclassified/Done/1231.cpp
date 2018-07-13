#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
const int size=60050,SS=size-2,ST=size-1;
struct Edge{
	int to,next,w;
} E[2000010];
int last[size]={},cnt=2;
void addEdge(int u,int v,int w){
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
	++cnt;
}
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
int dis[size];
bool BFS(){
	memset(dis,0,sizeof(dis));
	std::queue<int> q;
	q.push(ST);
	dis[ST]=1;
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=last[u];i;i=E[i].next)
			if(E[i^1].w && !dis[E[i].to]){
				dis[E[i].to]=dis[u]+1;
				q.push(E[i].to); 
			}
	}
	return dis[SS];
}
int cur[size];
int DFS(int u,int f){
	if(u==ST||f==0)return f;
	int res=0,v;
	for(int i=(cur[u]?cur[u]:last[u]);i;i=E[i].next)
		if(dis[u]==dis[E[i].to]+1 && E[i].w && (v=DFS(E[i].to,std::min(f-res,E[i].w)))){
			E[i].w-=v,E[i^1].w+=v;
			res+=v;
			cur[u]=i;
			if(res==f)return res;
		}
	return res;
}
int main(){
	int n1,n2,n3,m1,m2;
	n1=read();
	n2=read();
	n3=read();
	for(int i=1;i<=n2;++i){
		addEdge(SS,n1+n1+i,1);
		addEdge(n1+n1+i,SS,0);
	}
	for(int i=1;i<=n3;++i){
		addEdge(n1+n1+n2+i,ST,1);
		addEdge(ST,n1+n1+n2+i,0);
	}
	m1=read();
	int u,v;
	for(int i=0;i<m1;++i){
		u=read();
		v=read()+n1+n1;
		addEdge(v,u,1);
		addEdge(u,v,0);
	}
	for(int i=1;i<=n1;++i){
		addEdge(i,i+n1,1);
		addEdge(i+n1,i,0);
	}
	m2=read();
	for(int i=0;i<m2;++i){
		u=read()+n1;
		v=read()+n1+n1+n2;
		addEdge(u,v,1);
		addEdge(v,u,0);
	}
	int ans=0;
	while(BFS()){
		memset(cur,0,sizeof(cur));
		while(true){
			int k=DFS(SS,1<<20);
			if(k)ans+=k;
			else break;
		}
	}
	printf("%d\n",ans);
	return 0;
}

