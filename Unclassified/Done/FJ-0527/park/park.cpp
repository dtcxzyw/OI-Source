#include <cstdio>
#include <cstring>
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
const int size=100001;
struct Edge{
	int to,next,w;
} E[200001];
int last[size],cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[size],q[size];
bool flag[size];
inline int nxt(int x){
	++x;
	if(x<size)return x;
	return 0;
}
void SPFA(int s){
	memset(dis,0x3f,sizeof(dis));
	memset(flag,0,sizeof(flag));
	dis[s]=0,q[0]=s,flag[s]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=nxt(b);
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			int nd=dis[u]+E[i].w;
			if(dis[v]>nd){
				dis[v]=nd;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=nxt(e);
				}
			}
		}
	}
}
bool ring;
const int inf=0x3f3f3f3f;
int mlen;
void DFS(int u){
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(E[i].w==0 && dis[v]!=inf){
			if(flag[v])ring=true;
			else DFS(v);
		}
		if(ring)return;
	}
}
int k,p,n,num[size][51];
int DFS(int u,int off){
	if(u==n)return 1;
	int sum=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		int noff=off+(E[i].w-(dis[v]-dis[u]));
		if(noff<=k)
			sum=(sum+DFS(v,noff))%p;
	}
	return sum;
}
void foo(){
	cnt=0;
	memset(last,0,sizeof(last));
	n=read();
	int m=read();
	k=read();
	p=read();
	int u,v,w;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
	}
	SPFA(1);
	mlen=dis[n]+k;
	ring=false;
	memset(flag,0,sizeof(flag));
	DFS(1);
	if(ring)puts("-1");
	else printf("%d\n",DFS(1,0));
}
int main(){
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;++i)foo();
	return 0;
}

