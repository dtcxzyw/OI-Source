#include <cstdio>
#include <cstring>
const int size=100001;
struct Edge{
	int to,next,w;
} E[size<<2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[size],q[size];
bool flag[size];
void SPFA(int s){
	memset(dis,0x3f,sizeof(dis));
	memset(flag,0,sizeof(flag));
	dis[s]=0,flag[s]=true,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int nd=dis[u]+E[i].w;
			if(dis[E[i].to]>nd){
				dis[E[i].to]=nd;
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					if(dis[E[i].to]<dis[q[b]]){
						b=(b-1+size)%size;
						q[b]=E[i].to;
					}
					else{
						q[e]=E[i].to;
						e=(e+1)%size;
					}
				}
			}
		}
	}
}
int main(){
	int n,m,a,b,c;
	scanf("%d%d%d%d%d",&m,&n,&a,&b,&c);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	SPFA(a);
	int ans=dis[b]<dis[c]?dis[b]:dis[c];
	SPFA(b);
	ans+=dis[c];
	printf("%d\n",ans);
	return 0;
}

