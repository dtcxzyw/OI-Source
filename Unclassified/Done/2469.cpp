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
const int size=1800;
struct Edge{
	int src,to,next,w,c;
} E[40000];
const int SS=size-1,ST=size-2;
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int w,int c){
	++cnt;
	E[cnt].src=u,E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w,E[cnt].c=c;
	last[u]=cnt;
}
void addEdge(int u,int v,int w){
	addEdgeImpl(u,v,w,1);
	addEdgeImpl(v,u,-w,0);
}
int q[size*100],eid[size],nf[size],dis[size];
bool flag[size];
int minv(int a,int b){
	return a<b?a:b;
}
bool SPFA(){
	memset(flag,0,sizeof(flag));
	memset(dis,0x3f,sizeof(dis));
	q[0]=SS,nf[SS]=1<<30,dis[SS]=0,flag[SS]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].c>0 && dis[u]+E[i].w<dis[v]){
				dis[v]=dis[u]+E[i].w;
				nf[v]=minv(nf[u],E[i].c);
				eid[v]=i;
				if(!flag[v]){
					flag[v]=true;
					q[e++]=v;
				}
			}
		}
	}
	return dis[ST]!=0x3f3f3f3f;
}
int MCMF(){
	int res=0;
	while(SPFA()){
		int p=ST,f=nf[ST];
		while(p!=SS){
			E[eid[p]].c-=f;
			E[eid[p]^1].c+=f;
			p=E[eid[p]].src;
		}
		res+=dis[ST]*f;
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		addEdge(SS,i,0);
		addEdge(SS,i+n,read());
		addEdge(i+n,ST,0);
	}
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int w=read();
		if(u<v)addEdge(u,v+n,w);
		else addEdge(v,u+n,w);
	}
	printf("%d\n",MCMF());
	return 0;
}

