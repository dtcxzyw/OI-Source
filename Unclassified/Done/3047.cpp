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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
const int size=100001;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int dp[size][21]={},k,p[size];
void DFS1(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v){
			p[v]=u;
			DFS1(v);
			for(int j=1;j<=k;++j)
				dp[u][j]+=dp[v][j-1];
		}
	}
}
void DFS2(int u){
	for(int i=k;i>=1;--i){
		dp[u][i]+=dp[p[u]][i-1];
		if(u!=1 && i>=2)dp[u][i]-=dp[u][i-2];
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v)
			DFS2(v);
	}
}
int main(){
	int n=read();
	k=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	for(int i=1;i<=n;++i)
		dp[i][0]=read();
	DFS1(1);
	DFS2(1);
	for(int i=1;i<=n;++i){
		int sum=0;
		for(int j=0;j<=k;++j)sum+=dp[i][j];
		print(sum);
	}
	return 0;
}

