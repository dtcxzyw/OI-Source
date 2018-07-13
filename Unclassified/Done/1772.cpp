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
const int num=25,size=110;
struct Edge{
	int to,next,w;
} E[num*num];
int last[num]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[num]={},q[num];
bool vis[num]={},mark[num];
void SPFA(){
	memset(dis,0x3f,sizeof(dis));
	int b=0,e=1;
	q[b]=1,vis[1]=true,dis[1]=0;
	while(b!=e){
		int u=q[b];
		vis[u]=false;
		b=(b+1)%num;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(mark[v] && dis[v]>dis[u]+E[i].w){
				dis[v]=dis[u]+E[i].w;
				if(!vis[v]){
					vis[v]=true;
					q[e]=v;
					e=(e+1)%num;
				}
			}
		}
	}
}
int f[size][size],dp[size]={};
bool flag[num][size];
int main(){
	int n=read();
	int m=read();
	int k=read();
	int e=read();
	for(int i=0;i<e;++i){
		int u=read();
		int v=read();
		int w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	memset(flag,0xff,sizeof(flag));
	int d=read();
	for(int i=0;i<d;++i){
		int p=read();
		int a=read();
		int b=read();
		for(int j=a;j<=b;++j)flag[p][j]=false;
	}
	for(int i=1;i<=n;++i){
		memset(mark,0xff,sizeof(mark));
		for(int j=i;j<=n;++j){
			for(int k=1;k<=m;++k)mark[k]&=flag[k][j];
			SPFA();
			f[i][j]=dis[m];
		}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=-k;
	for(int i=1;i<=n;++i)
		for(int j=0;j<i;++j)
			if(f[j+1][i]!=0x3f3f3f3f){
				int val=dp[j]+k+f[j+1][i]*(i-j);
				if(dp[i]>val)dp[i]=val;
			}
	printf("%d\n",dp[n]);
	return 0;
}

