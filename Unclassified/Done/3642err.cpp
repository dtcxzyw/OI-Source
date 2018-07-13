#include <cstdio>
#include <algorithm>
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
const int size=3000100;
struct Edge{
	int to,next,w;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int buf[size];
int iabs(int x){
	return x>=0?x:-x;
}
int d[size]={};
long long DFS(int u){
	long long res=0;
	for(int i=last[u];i;i=E[i].next)res+=DFS(E[i].to);
	int p=0;
	for(int i=last[u];i;i=E[i].next)buf[p++]=E[i].w+d[E[i].to];
	if(p){
		std::nth_element(buf,buf+p/2,buf+p);
		d[u]=buf[p/2];
		for(int i=0;i<p;++i)
			res+=iabs(buf[i]-d[u]);
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	for(int i=2;i<=n+m;++i){
		int p=read();
		addEdge(p,i,read());
	}
	printf("%lld\n",DFS(1));
	return 0;
}

