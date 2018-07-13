#include <cstdio>
const int size=100010;
struct Edge{
	int to,next,w;
} E[size*3];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
long long dis[size]={};
int q[size],rcnt[size]={};
bool flag[size]={};
bool SPFA(int n){
	dis[0]=0,flag[0]=true,q[0]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			long long nd=dis[u]+E[i].w;
			int v=E[i].to;
			if(dis[v]<nd){
				if(++rcnt[v]>=n)return false;
				dis[v]=nd;
				if(!flag[v]){
					flag[v]=true;
					if(dis[v]>dis[q[b]]){
						b=(b-1+size)%size;
						q[b]=v;
					}
					else{
						q[e]=v;
						e=(e+1)%size;
					}
				}
			}
		}
	}
	return true;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int x,u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&x,&u,&v);
		switch(x){
		case 1:addEdge(u,v,0),addEdge(v,u,0);break;//u==v -> u-v<=0,v-u<=0
		case 2:addEdge(u,v,1);break;//u<v -> u-v<=-1
		case 3:addEdge(v,u,0);break;//u>=v -> v-u<=0
		case 4:addEdge(v,u,1);break;//u>v -> v-u<=-1
		case 5:addEdge(u,v,0);break;//u<=v -> u-v<=0
		}
	}
	for(int i=n;i>=1;--i)
		addEdge(0,i,1);
	if(SPFA(n+1)){
		long long sum=0;
		for(int i=1;i<=n;++i)
			sum+=dis[i];
		printf("%lld\n",sum);
	}
	else puts("-1");
	return 0;
}

