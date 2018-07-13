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
const int size=200005*2,S=size-1,T=size-2,inf=1<<30;
struct Edge{
	int to,next,f,w;
} E[size*6];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int f,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f,E[cnt].w=w;
	last[u]=cnt;
}
void addEdge(int u,int v,int f,int w){
	addEdgeImpl(u,v,f,w);
	addEdgeImpl(v,u,0,-w);
}
int dis[size],q[size],eid[size];
bool flag[size]={};
bool SPFA(){
	memset(dis,0x3f,sizeof(dis));
	dis[S]=0,q[0]=S;
	flag[S]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		flag[u]=false;
		if(b==size)b=0;
		for(int i=last[u];i;i=E[i].next)
			if(E[i].f){
				int v=E[i].to;
				int cd=dis[u]+E[i].w;
				if(cd<dis[v]){
					dis[v]=cd;
					eid[v]=i;
					if(!flag[v]){
						flag[v]=true;
						q[e++]=v;
						if(e==size)e=0;
					}
				}
			}
	}
	return dis[T]!=0x3f3f3f3f;
}
long long MCMF(){
	long long res=0;
	while(SPFA()){
		int mf=inf,p=T;
		while(p!=S){
			int e=eid[p];
			if(mf>E[e].f)mf=E[e].f;
			p=E[e^1].to;
		}
		res+=1LL*dis[T]*mf;
		p=T;
		while(p!=S){
			int e=eid[p];
			E[e].f-=mf;
			E[e^1].f+=mf;
			p=E[e^1].to;
		}
	}
	return res;
}
int A[size/2];
int main(){
	int n=read();
	for(int i=1;i<=n;++i)A[i]=read();
	int p=read();
	int m1=read();
	int c1=read();
	int m2=read();
	int c2=read();
	for(int i=1;i<=n;++i){
		addEdge(S,i,A[i],0);
		if(i!=n)addEdge(i,i+1,inf,0);
		addEdge(i+n,T,A[i],0);
		if(i+m1<=n)addEdge(i,i+m1+n,inf,c1);
		if(i+m2<=n)addEdge(i,i+m2+n,inf,c2);
		addEdge(S,i+n,inf,p);
	}
	printf("%lld\n",MCMF());
	return 0;
}

