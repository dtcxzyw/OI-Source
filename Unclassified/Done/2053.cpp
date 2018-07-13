#include <cstdio>
#include <cstring>
struct Edge{
	int src,to,next,w,c;
} E[100000];
const int size=1000,SS=size-1,ST=size-2;
int last[1000],cnt=1;
void addEdgeImpl(int u,int v,int w,int c){
	++cnt;
	E[cnt].src=u,E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w,E[cnt].c=c;
	last[u]=cnt;
}
void addEdge(int u,int v,int w,int c){
	addEdgeImpl(u,v,w,c);
	addEdgeImpl(v,u,-w,0);
}
const int maxv=1<<30;
int q[size],dis[size],eid[size],f[size];
bool flag[size];
int minv(int a,int b){
	return a<b?a:b;
}
bool SPFA(){
	memset(dis,0x3f,sizeof(dis));
	memset(flag,0,sizeof(flag));
	q[0]=SS,dis[SS]=0,f[SS]=1<<30,flag[SS]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(dis[v]>dis[u]+E[i].w && E[i].c>0){
				dis[v]=dis[u]+E[i].w;
				f[v]=minv(f[u],E[i].c);
				eid[v]=i;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
	return dis[ST]!=0x3f3f3f3f;
}
int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;++i)addEdge(SS,i,0,1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			addEdge(n+i*m+j,ST,0,1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			int w;
			scanf("%d",&w);
			for(int k=1;k<=n;++k)
				addEdge(i,n+j+k*m,w*k,1);
		}
	int ans=0;
	while(SPFA()){
		int p=ST,nf=f[ST];
		while(p!=SS){
			E[eid[p]].c-=nf;
			E[eid[p]^1].c+=nf;
			p=E[eid[p]].src;
		}
		ans+=nf*dis[ST];
	}
	printf("%.2lf",static_cast<double>(ans)/n);
	return 0;
}

