#include <cstdio>
#include <cstring>
const int size=50001;
struct Edge{
	int to,next;
} E[size<<1];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
long long siz2[size],dis[size],dp[size],n;
bool flag[size];
void init(int u){
	flag[u]=true,siz2[u]=2;
	for(int i=last[u];i;i=E[i].next)
		if(!flag[E[i].to]){
			dis[E[i].to]=dis[u]+1;
			init(E[i].to);
			siz2[u]+=siz2[E[i].to];
		}
}
void dfs(int u){
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next)
		if(!flag[E[i].to]){
			dp[E[i].to]=dp[u]+n-siz2[E[i].to];
			dfs(E[i].to);
		}
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	n=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	dis[1]=0;
	memset(flag,0,sizeof(flag));
	init(1);
	for(int i=2;i<=n;++i)
		dp[1]+=dis[i];
	memset(flag,0,sizeof(flag));
	dfs(1);
	int maxi=1;
	for(int i=2;i<=n;++i)
		if(dp[i]<dp[maxi])
			maxi=i;
	printf("%d %lld\n",maxi,dp[maxi]);
	return 0;
}

