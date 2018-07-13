#include <cstdio>
#include <cstring>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
inline void print(long long x){
	printImpl(x);
	putchar('\n');
}
const int size=200100;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
long long fa[size],w[size],p[size],q[size],l[size],dp[size];
void CAS(long long& a,long long b){
	if(a>b)a=b;
}
void DFS(int u){
	{
		int cp=u;
		long long cl=0;
		while(fa[cp]){
			cl+=w[cp];
			if(cl<=l[u])CAS(dp[u],dp[fa[cp]]+cl*p[u]+q[u]);
			else break;
			cp=fa[cp];
		}
	}
	for(int i=last[u];i;i=E[i].next)
		DFS(E[i].to);
}
int main(){
	int n=read();
	int t=read();
	for(int i=2;i<=n;++i){
		fa[i]=read();
		w[i]=read();
		addEdge(fa[i],i);
		p[i]=read();
		q[i]=read();
		l[i]=read();
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1]=0;
	DFS(1);
	for(int i=2;i<=n;++i)
		print(dp[i]);
	return 0;
}

