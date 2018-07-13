#include <cstdio>
#include <queue>
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
const int size=100005;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
struct Info{
	int pos,dis;
	bool operator<(const Info rhs) const{
		return dis>rhs.dis;
	}
} A[size];
std::priority_queue<Info> heap;
int dis[size],id[size],f[size]={},g[size]={},lid[size]={},q[size],ins[size];
bool flag[size]={},in[size];
void SPFA(int s,int st,int eid,int pid){
	memset(in,0,sizeof(in));
	int b=0,e=1,top=0;
	q[0]=s;
	dis[s]=st;
	flag[s]=true;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			if(i==eid)continue;
			int v=E[i].to;
			if(lid[v]>pid){
				int d=dis[u]+E[i].w+g[lid[v]];
				if(!in[v]){
					ins[top++]=v;
					in[v]=true;
					A[v].dis=d;
				}
				else A[v].dis=std::min(A[v].dis,d);
			}
			else{
				int d=dis[u]+E[i].w;
				if(dis[v]>d){
					dis[v]=d;
					if(!flag[v]){
						flag[v]=true;
						q[e]=v;
						e=(e+1)%size;
					}
				}
			}
		}
	}
	while(top)heap.push(A[ins[--top]]);
}
int main(){
	int n=read();
	int m=read();
	int l=read();
	for(int i=1;i<=m;++i){
		int u=read();
		int v=read();
		int w=read();
		addEdge(u,v,w);
	}
	A[1].pos=lid[1]=1;
	for(int i=1;i<=l;++i){
		id[i]=read();
		int v=E[id[i]].to;
		A[v].pos=lid[v]=i+1;
	}
	for(int i=1;i<=l;++i)
		f[i]=f[i-1]+E[id[i]].w;
	for(int i=l;i>=1;--i)
		g[i]=g[i+1]+E[id[i]].w;
	memset(dis,0x3f,sizeof(dis));
	E[0].to=1;
	for(int i=1;i<=l;++i){
		SPFA(E[id[i-1]].to,f[i-1],id[i],i);
		while(!heap.empty() && heap.top().pos<=i)heap.pop();
		if(heap.empty())puts("-1");
		else printf("%d\n",heap.top().dis);
	}
	return 0;
}

