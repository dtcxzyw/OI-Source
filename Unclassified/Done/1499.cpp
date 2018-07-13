#include <cstdio>
#include <algorithm>
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
const int size=100005;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool flag[size];
int st[size][2],ssiz=0,ring[size][2],rsiz=0;
bool findRing(int u,int src,int d){
	if(flag[u]){
		int v;
		do{
			--ssiz;
			v=st[ssiz][0];
			++rsiz;
			ring[rsiz][0]=v;
			ring[rsiz+1][1]=st[ssiz][1];
		}
		while(u!=v);
		ring[1][1]=d;
		return true;
	}
	st[ssiz][0]=u;
	st[ssiz][1]=d;
	++ssiz;
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=src && findRing(v,u,E[i].w))return true;
	}
	--ssiz;
	flag[u]=false;
	return false;
}
long long dp[size]={},ans=0;
void DFS(int u,int p){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p && !flag[v]){
			DFS(v,u);
			long long dis=dp[v]+E[i].w;
			ans=std::max(ans,dp[u]+dis);
			dp[u]=std::max(dp[u],dis);
		}
	}
}
long long S[size],L[size][3],R[size][3];
const long long inf=1LL<<60;
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		int u=read();
		int v=read();
		int w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	memset(flag,0,sizeof(flag));
	findRing(1,0,0);
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=rsiz;++i)flag[ring[i][0]]=true;
	for(int i=1;i<=rsiz;++i)DFS(ring[i][0],0);
	for(int i=1;i<=rsiz;++i)S[i]=S[i-1]+ring[i][1];
	L[0][0]=L[0][1]=L[0][2]=-inf;
	for(int i=1;i<=rsiz;++i){
		int u=ring[i][0];
		long long dis=S[i]-S[1];
		L[i][0]=std::max(L[i-1][0],dp[u]+dis);
		L[i][1]=std::max(L[i-1][1],dp[u]-dis);
		L[i][2]=std::max(L[i-1][2],dp[u]+dis+L[i-1][1]);
	}
	R[rsiz+1][0]=R[rsiz+1][1]=R[rsiz+1][2]=-inf;
	for(int i=rsiz;i>=1;--i){
		int u=ring[i][0];
		long long dis=S[rsiz]-S[i];
		R[i][0]=std::max(R[i+1][0],dp[u]+dis);
		R[i][1]=std::max(R[i+1][1],dp[u]-dis);
		R[i][2]=std::max(R[i+1][2],dp[u]+dis+R[i+1][1]);
	}
	long long res=L[rsiz][2];
	for(int i=1;i<rsiz;++i)
		res=std::min(res,std::max(ring[1][1]+L[i][0]+R[i+1][0],std::max(L[i][2],R[i+1][2])));
	ans=std::max(ans,res);
	printf("%lld.%d\n",ans>>1,ans&1?5:0);
	return 0;
}

