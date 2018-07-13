#include <cstdio>
#include <cstring>
const int size=1010;
struct Edge{
	int src,to,next,f,c,w;
} E[30010];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int c,int w){
	++cnt;
	E[cnt].src=u,E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c,E[cnt].w=w,E[cnt].f=0;
	last[u]=cnt;
}
void addEdge(int u,int v,int c,int w){
	addEdgeImpl(u,v,c,w);
	addEdgeImpl(v,u,0,-w);
}
bool flag[size];
int n,d[size],q[size];
bool BFS(){
	memset(flag,0,sizeof(flag));
	memset(d,0,sizeof(d));
	int b=0,e=1;
	q[0]=1,flag[1]=true,d[1]=0;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(!flag[v] && E[i].f<E[i].c){
				flag[v]=true;
				d[v]=d[u]+1;
				q[e++]=v;
			}	
		}
	}
	return flag[n];
}
int minv(int a,int b){
	return a<b?a:b;
}
int now[size];
int DFS(int u,int f){
	if(u==n || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(E[i].c-E[i].f,f)))>0){
			res+=k,f-=k;
			E[i].f+=k,E[i^1].f-=k;	
			if(f==0)break;
		}
	}
	return res;
}
int dinic(){
	int res=0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		res+=DFS(1,1<<30);
	}
	return res;
}
int eid[size];
bool SPFA(int s){
	memset(d,0x3f,sizeof(d));
	memset(flag,0,sizeof(flag));
	int b=0,e=1;
	q[0]=s,flag[s]=true,d[s]=0;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(d[v]>d[u]+E[i].w && E[i].c>E[i].f){
				eid[v]=i;
				d[v]=d[u]+E[i].w;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
	return d[n]!=0x3f3f3f3f;
}
int MCMF(int k){
	int ans=0;
	while(SPFA(0)){
		int p=n,nf=k;
		while(p!=0){
			nf=minv(nf,E[eid[p]].c-E[eid[p]].f);
			p=E[eid[p]].src;
		}
		p=n;
		while(p!=0){
			E[eid[p]].f+=nf;
			E[eid[p]^1].f-=nf;
			ans+=E[eid[p]].w*nf;
			p=E[eid[p]].src;
		}
	}	
	return ans;
}
int main(){
	int m,k;
	scanf("%d%d%d",&n,&m,&k);
	int u,v,c,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d%d",&u,&v,&c,&w);
		addEdge(u,v,c,w);
	}
	printf("%d ",dinic());
	int old=cnt;
	for(int i=2;i<=old;i+=2){
		addEdge(E[i].src,E[i].to,1<<30,E[i].w);
		E[i].w=E[i^1].w=0;
	}
	addEdge(0,1,k,0);
	printf("%d\n",MCMF(k));
	return 0;
}

