#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
const int size=3200,S=size-1,T=size-2;
struct Edge{
	int to,next,f;
} E[15*size];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,int f){
	addEdgeImpl(u,v,1);
	addEdgeImpl(v,u,0);
}
int q[size],d[size];
bool BFS(){
	memset(d,-1,sizeof(d));
	int b=0,e=1;
	q[0]=S,d[S]=0;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(d[v]==-1 && E[i].f){
				d[v]=d[u]+1;	
				q[e++]=v;
			}
		}
	}
	return d[T]!=-1;
}
int now[size],nxt[size];
int DFS(int u,int mf){
	if(u==T || mf==0)return mf;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,std::min(mf,E[i].f)))>0){
			E[i].f-=k;
			E[i^1].f+=k;
			res+=k;
			mf-=k;
			nxt[u>>1]=v>>1;
			if(mf==0)break;
		}
	}
	if(res==0)d[u]=-1;
	return res;
}
int dinic(){
	int res=0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		res+=DFS(S,1<<30);
	}
	return res;
}
int id[size];
bool flag[size]={};
int main(){
	int n;
	scanf("%d",&n);
	memset(nxt,-1,sizeof(nxt));
	int c=0,u=0;
	while(c<=n){
		++u;
		for(int i=sqrt(u)+1;;++i){
			int v=i*i-u;
			if(v<u)addEdge(v<<1,u<<1|1,1);
			else break;
		}
		addEdge(S,u<<1,1);
		addEdge(u<<1|1,T,1);
		if(dinic()==0)id[++c]=u;
	}
	printf("%d\n",u-1);
	for(int i=1;i<=n;++i)
		if(!flag[id[i]]){
			int p=id[i];
			do{
				printf("%d ",p);
				flag[p]=true;
				p=nxt[p];
			}while(p!=-1 && !flag[p] && p!=(S>>1));
			putchar('\n');
		}
	return 0;
}

