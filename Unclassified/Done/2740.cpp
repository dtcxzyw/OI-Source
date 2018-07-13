#include <cstdio>
#include <cstring>
const int size=210;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=1;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int minv(int a,int b){
	return a<b?a:b;
}
int n,eid[size],pre[size],f[size],q[size];
bool flag[size]={};
int BFS(){
	memset(flag,0,sizeof(flag));
	memset(f,0,sizeof(f));
	memset(pre,0,sizeof(pre));
	q[0]=1,f[1]=0x3f3f3f3f,flag[1]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		if(u==n){
			int p=n;
			do{
				E[eid[p]].w-=f[n];
				E[eid[p]^1].w+=f[n];
				p=pre[p];
			}while(p);
			return f[n];
		}
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to,nf=minv(E[i].w,f[u]);
			if(nf>f[v]){
				f[v]=nf;
				pre[v]=u;
				eid[v]=i;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
	return 0;
}
int main(){
	int m;
	scanf("%d%d",&m,&n);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,0);
	}
	int ans=0;
	while(true){
		int k=BFS();
		if(k)ans+=k;
		else break;
	}
	printf("%d\n",ans);
	return 0;
}

