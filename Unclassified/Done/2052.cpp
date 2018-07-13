#include <cstdio>
const int size=1000001;
struct Edge{
	int to,next,w;
} E[2000001];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int n,siz[size];
long long ans=0;
int sub(int a,int b){
	return a>b?a-b:b-a; 
}
bool flag[size]={};
void dfs(int u){
	flag[u]=true;
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			dfs(v);
			ans+=1LL*E[i].w*sub(siz[v],n-siz[v]);
			siz[u]+=siz[v];
		}
	}
}
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
int main(){
	n=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	dfs((n+1)>>1);
	printf("%lld\n",ans);
	return 0;
}

