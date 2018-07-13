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
const int size=40001;
struct Edge{
	int to,next;
} E[80010];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int dis[3][size],q[size*5];
bool flag[size];
void SPFA(int s,int* d){
	memset(flag,0,sizeof(flag));
	int b=0,e=1;
	flag[s]=true,q[0]=s,d[s]=0;
	while(b!=e){
		int u=q[b++];
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(d[v]>d[u]+1){
				d[v]=d[u]+1;
				if(!flag[v]){
					flag[v]=true;
					q[e++]=v;
				}
			}
		}
	}
}
int main(){
	int b,e,p,n,m;
	b=read();
	e=read();
	p=read();
	n=read();
	m=read();
	int u,v;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	memset(dis,0x3f,sizeof(dis));
	SPFA(1,dis[0]);
	SPFA(2,dis[1]);
	SPFA(n,dis[2]);
	int ans=1<<30;
	for(int i=1;i<=n;++i){
		int w=dis[0][i]*b+dis[1][i]*e+dis[2][i]*p;
		if(ans>w)ans=w;
	}
	printf("%d\n",ans);
	return 0;	
}

