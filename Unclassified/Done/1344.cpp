#include <cstdio>
#include <cstring>
typedef long long Int64;
struct Edge{
	Int64 to,next,f,c;
} E[2010];
const Int64 size=40;
Int64 last[size]={},cnt=1;
void addEdgeImpl(Int64 u,Int64 v,Int64 c){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c,E[cnt].f=0;
	last[u]=cnt;
}
void addEdge(Int64 u,Int64 v,Int64 c){
	addEdgeImpl(u,v,c);
	addEdgeImpl(v,u,0);
}
Int64 n,d[size],q[size];
bool flag[size];
bool BFS(){
	memset(d,0,sizeof(d));
	memset(flag,0,sizeof(flag));
	Int64 b=0,e=1;
	q[0]=1,flag[1]=true;
	while(b!=e){
		Int64 u=q[b++];
		for(Int64 i=last[u];i;i=E[i].next){
			Int64 v=E[i].to;
			if(!flag[v] && E[i].c>E[i].f){
				d[v]=d[u]+1;
				flag[v]=true;
				q[e++]=v;
			}
		}
	}
	return flag[n];
}
Int64 minv(Int64 a,Int64 b){
	return a<b?a:b;
}
Int64 now[size];
Int64 DFS(Int64 u,Int64 f){
	if(u==n || f==0)return f;
	Int64 res=0,k;
	for(Int64& i=now[u];i;i=E[i].next){
		Int64 v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].c-E[i].f)))>0){
			res+=k,f-=k;
			E[i].f+=k,E[i^1].f-=k;
			if(f==0)break;
		}
	}
	return res;
}
Int64 dinic(){
	Int64 ans=0;
	while(BFS()){
		memcpy(now,last,sizeof(last));
		ans+=DFS(1,1LL<<60);
	}
	return ans;
}
const int x=2000;
int main(){
	Int64 m;
	scanf("%lld%lld",&n,&m);
	Int64 u,v,w;
	for(Int64 i=0;i<m;++i){
		scanf("%lld%lld%lld",&u,&v,&w);
		addEdge(u,v,w*x+1);
	}
	Int64 res=dinic();
	printf("%lld %lld\n",res/x,res%x);
	return 0;
}

