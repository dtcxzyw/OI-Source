#include <cstdio>
#include <queue>
const int size=100001;
struct Edge{
	int to,next;
} E[200001];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int in[size]={},dp[size];
void top(int n){
	std::queue<int> q;
	for(int i=1;i<=n;++i){
		dp[i]=1;
		if(!in[i])q.push(i);
	}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int j=last[u];j;j=E[j].next)
			if(!--in[E[j].to])
				q.push(E[j].to),dp[E[j].to]+=dp[u];
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		++in[v];
	}
	
	top(n);
	
	for(int i=1;i<=n;++i)
		printf("%d\n",dp[i]);
	return 0;
}

