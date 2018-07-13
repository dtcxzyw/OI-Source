#include <cstdio>
#include <cstring>
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
const int size=4010;
struct Edge{
	int to,next,f;
} E[2*60100];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,int f){
	addEdgeImpl(u,v,f);
	addEdgeImpl(v,u,0);
}
int s,t,q[size],d[size];
bool BFS(){
	memset(d,0,sizeof(d));
	d[s]=1,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].f && d[v]==0){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[t];
}
int now[size];
int DFS(int u,int f){
	if(u==t || f==0)return f;
	long long res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,std::min(f,E[i].f)))){
			E[i].f-=k,E[i^1].f+=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	if(res==0)d[u]=0;
	return res;
}
void dinic(){
	while(BFS()){
		memcpy(now,last,sizeof(now));
		DFS(s,1<<30);
	}
}
int dfn[size]={},icnt=0,low[size],stack[size],top=0,col[size],ccnt=0;
bool flag[size]={};
void tarjan(int u){
	dfn[u]=low[u]=++icnt;
	stack[++top]=u;
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next)
		if(E[i].f){
			int v=E[i].to;
			if(dfn[v]){
				if(flag[v] && dfn[v]<low[u])
					low[u]=dfn[v];
			}
			else{
				tarjan(v);
				if(low[v]<low[u])low[u]=low[v];
			}
		}
	if(dfn[u]==low[u]){
		++ccnt;
		int v;
		do{
			v=stack[top--];
			flag[v]=false;
			col[v]=ccnt;
		}while(v!=u);
	}
}
int main(){
	int n=read();
	int m=read();
	s=read();
	t=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int c=read();
		addEdge(u,v,c);
	}
	dinic();
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	for(int i=1;i<=m;++i){
		int id=i<<1;
		if(E[id].f)puts("0 0");
		else{
			int u=E[id^1].to,v=E[id].to;
			printf("%d %d\n",col[u]!=col[v],col[s]==col[u] && col[v]==col[t]);
		}
	}
	return 0;
}

