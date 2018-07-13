#include <cstdio>
#include <cstring>
struct Edge{
	int to,next;
} E[4000001];
const int size=1000001;
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int dis[size],c[size]={},q[size];
bool flag[size]={};
void SPFA(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	q[0]=1;
	c[1]=1;
	flag[1]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int nd=dis[u]+1;
			if(dis[E[i].to]>nd){
				dis[E[i].to]=nd;
				c[E[i].to]=0;
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					q[e]=E[i].to;
					e=(e+1)%size;
				}
			}
			
			if(dis[E[i].to]==nd)
				c[E[i].to]=(c[E[i].to]+c[u])%100003;
		}
		
		flag[u]=false;
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	SPFA();
	for(int i=1;i<=n;++i)
		printf("%d\n",c[i]);
	return 0;
}

