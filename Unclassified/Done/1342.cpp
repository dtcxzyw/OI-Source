#include <cstdio>
#include <cstring>
const int size=1001;
struct Edge{
	int to,next,w;
} E[200010];
int last[2][size]={},cnt=0;
void addEdge(int u,int v,int w,int d){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[d][u],E[cnt].w=w;
	last[d][u]=cnt;
}
int dis[2][size];
int q[size];
bool flag[size];
void SPFA(int d){
	memset(flag,0,sizeof(flag));
	memset(dis[d],0x3f,sizeof(dis[d]));
	q[0]=1,flag[1]=true,dis[d][1]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[d][u];i;i=E[i].next){
			int v=E[i].to;
			long long nd=dis[d][u]+E[i].w;
			if(dis[d][v]>nd){
				dis[d][v]=nd;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n,m;
	n=read();
	m=read();
	int u,v,w;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w,0);
		addEdge(v,u,w,1);
	}
	SPFA(0);
	SPFA(1);
	int ans=0;
	for(int i=2;i<=n;++i)
		ans+=dis[0][i]+dis[1][i];
	printf("%d\n",ans);
	return 0;
}

