#include <cstdio>
#include <cstring>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100001;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool flag[size]={};
int dp[size];
int minv(int a,int b){
	return a<b?a:b;
}
void DFS(int u){
	flag[u]=true;
	int sum=0,cc=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			++cc;
			DFS(v);
			sum+=minv(dp[v],E[i].w);
		}
	}
	if(cc)dp[u]=sum;
}
int main(){
	int n,s;
	n=read();
	s=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	memset(dp,0x3f,sizeof(dp));
	DFS(s);
	printf("%d\n",dp[s]);
	return 0;	
}

