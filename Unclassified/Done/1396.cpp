#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=10001;
struct Edge{
	int to,next,w;
} E[40001];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int minv[size],q[size];
bool flag[size]={};
void SPFA(int s){
	memset(minv,0x3f,sizeof(minv));
	q[0]=s,flag[s]=true,minv[s]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int nd=std::max(minv[u],E[i].w);
			if(minv[E[i].to]>nd){
				minv[E[i].to]=nd;
				if(!flag[E[i].to]){
					flag[E[i].to]=true;
					q[e]=E[i].to;
					e=(e+1)%size;
				}
			}
		}
	}
}
int main(){
	int n,m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	SPFA(s);
	printf("%d\n",minv[t]);
	return 0;
}

