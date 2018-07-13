#include <cstdio>
const int size=100010;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
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
int l[size],r[size],pcnt=0;
bool flag[size]={};
void DFS(int u){
	flag[u]=true;
	l[u]=++pcnt;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v])DFS(v);
	}
	r[u]=++pcnt;
}
int A[size*2];
void add(int i,int n,int v){
	while(i<=n){
		A[i]+=v;
		i+=i&-i;
	}
}
int query(int i){
	int res=0;
	while(i){
		res+=A[i];
		i-=i&-i;
	}
	return res;
}
int main(){
	int n=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	for(int i=0;i<n;++i){
		u=read();	
		printf("%d\n",query(l[u]));
		add(l[u],n*2,1);
		add(r[u],n*2,-1);
	}
	return 0;
}

