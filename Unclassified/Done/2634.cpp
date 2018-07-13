#include <cstdio>
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
const int size=20010;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int ans=0,dp[size][3]={};
void DFS(int u,int p){
	dp[u][0]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p){
			DFS(v,u);
			for(int j=0;j<3;++j)
				ans+=2*dp[u][(3-(j+E[i].w)%3)%3]*dp[v][j];
			for(int j=0;j<3;++j)
				dp[u][(j+E[i].w)%3]+=dp[v][j];
		}
	}
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(1,0);
	int a=ans+n,b=n*n;
	int d=gcd(a,b);
	printf("%d/%d\n",a/d,b/d);
	return 0;
}

