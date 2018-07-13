#include <cstdio>
#include <cstring>
#include <map>
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
const int size=201000;
struct Edge{
	int to,next;
} E[6*size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
std::map<int,int> edge[size];
void check(int u,int v,int id){
	if(u>v)std::swap(u,v);
	int& x=edge[u][v];
	if(x)addEdge(id,x),addEdge(x,id);
	else x=id;
}
int ans=0,len[size];
void DFS(int u,int p){
	len[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p){
			DFS(v,u);
			ans=std::max(ans,len[u]+len[v]);
			len[u]=std::max(len[u],len[v]+1);
		}
	}
}
int main(){
	int n=read();
	int tsiz=n-2;
	for(int i=1;i<=tsiz;++i){
		int a=read();
		int b=read();
		int c=read();
		check(a,b,i);
		check(b,c,i);
		check(c,a,i);
	}
	DFS(1,0);
	printf("%d\n",ans);
	return 0;
}

