#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=2001;
struct Info{
	int u,v,w;
	bool operator<(const Info& rhs) const{
		if(u!=rhs.u)return u<rhs.u;
		if(v!=rhs.v)return v<rhs.v;
		return w<rhs.w;
	}
} info[size*size];
struct Edge{
	int to,next,w;
} E[size*size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[size],q[size],num[size]={};
bool flag[size]={};
void SPFA(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0,q[0]=1,num[1]=1,flag[1]=true;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int nd=dis[u]+E[i].w;
			if(dis[E[i].to]>nd){
				dis[E[i].to]=nd;
				num[E[i].to]=num[u];
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					q[e]=E[i].to;
					e=(e+1)%size;
				}
			}
			else if(dis[E[i].to]==nd)
				num[E[i].to]+=num[u];
		}
	}
}
int main(){
	int n,e;
	scanf("%d%d",&n,&e);
	for(int i=0;i<e;++i)
		scanf("%d%d%d",&info[i].u,&info[i].v,&info[i].w);
	std::sort(info,info+e);
	int u=0,v=0;
	for(int i=0;i<e;++i)
		if(info[i].v!=v || info[i].u!=u){
			u=info[i].u,v=info[i].v;
			addEdge(u,v,info[i].w);
		}

	SPFA();
	if(dis[n]==0x3f3f3f3f)puts("No answer");
	else printf("%d %d\n",dis[n],num[n]);
	return 0;
}

