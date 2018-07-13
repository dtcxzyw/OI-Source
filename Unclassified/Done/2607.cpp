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
const int size=1000010;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
long long maxv(long long a,long long b){
	return a>b?a:b;
}
int w[size],p[size];
long long dp[size][2];
bool flag[size]={};
int end;
void DFS(int u){
	flag[u]=true;
	dp[u][0]=0;
	dp[u][1]=w[u];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(end==v)dp[v][1]=-1LL<<60;
		else{
			DFS(v);
			dp[u][0]+=maxv(dp[v][0],dp[v][1]);
			dp[u][1]+=dp[v][0];
		}
	}
}
long long ans=0;
void find(int u){
	while(!flag[u]){
		flag[u]=true;
		u=p[u];
	}
	end=u;
	DFS(u);
	long long x1=maxv(dp[u][0],dp[u][1]);
	end=u=p[u];
	DFS(u);
	long long x2=maxv(dp[u][0],dp[u][1]);
	ans+=maxv(x1,x2);
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		w[i]=read();
		p[i]=read();
		addEdge(p[i],i);	
	}
	for(int i=1;i<=n;++i)
		if(!flag[i])find(i);
	printf("%lld\n",ans);
	return 0;
}

