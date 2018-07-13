#include <cstdio>
#include <cstring>
const int size=65*4,S=size-1,T=size-2,inf=1<<30;
struct Edge{
	int to,next,f;
} E[size*size];
int last[size],cnt;
void addEdgeImpl(int u,int v,int f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,int f){
	addEdgeImpl(u,v,f);
	addEdgeImpl(v,u,0);
}
int d[size],q[size];
bool BFS(){
	memset(d,0,sizeof(d));
	q[0]=S,d[S]=1;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].f && !d[v]){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[T];
}
int minv(int a,int b){
	return a<b?a:b;
}
int now[size];
int DFS(int u,int f){
	if(u==T || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].f)))){
			E[i].f-=k,E[i^1].f+=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	if(res==0)d[u]=0;
	return res;
}
int dinic(){
	int res=0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		res+=DFS(S,inf);
	}
	return res;
}
//type 0       0   1       1
//side 0       1   0       1
//S-->MS--k-->MT-->WS--k-->WT-->T
//    -------------------->
int get(int u,int type,int side){
	return (u<<2)|(type<<1)|side;
}
char map[51][51];
void build(int w,int k,int n){
	memset(last,0,sizeof(last));
	cnt=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(map[i][j]=='Y')addEdge(get(i,0,0),get(j,1,1),1);
			else addEdge(get(i,0,1),get(j,1,0),1); 
	for(int i=1;i<=n;++i){
		addEdge(S,get(i,0,0),w);
		addEdge(get(i,0,0),get(i,0,1),k);
		addEdge(get(i,1,0),get(i,1,1),k);
		addEdge(get(i,1,1),T,w);
	}
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%s",map[i]+1);
	int l=0,r=50,ans=0;
	while(l<=r){
		int m=(l+r)>>1;
		build(m,k,n);
		if(dinic()>=n*m)l=m+1,ans=m;
		else r=m-1;
	}
	printf("%d\n",ans);
	return 0;
}

