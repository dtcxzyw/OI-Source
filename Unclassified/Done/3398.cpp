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
int p[size][18],d[size];
void DFS(int u){
	for(int i=1;i<18;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u][0]!=v){
			p[v][0]=u;
			d[v]=d[u]+1;
			DFS(v);
		}
	}
}
int query(int u,int v){
	if(d[u]<d[v])std::swap(u,v);
	int delta=d[u]-d[v];
	for(int i=0;i<18;++i)
		if(delta&(1<<i))
			u=p[u][i];
	if(u==v)return u;
	for(int i=17;i>=0;--i)
		if(p[u][i]!=p[v][i])
			u=p[u][i],v=p[v][i];
	return p[u][0];
}
int main(){
	int n=read();
	int q=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=0;
	DFS(1);
	int x,y,z,w;
	for(int i=0;i<q;++i){
		x=read();
		y=read();
		int lxy=query(x,y);
		z=read();
		w=read();
		int lzw=query(z,w);
		if(d[lxy]<d[lzw])
			lxy=lzw,z=x,w=y;
		puts((query(z,lxy)==lxy||query(w,lxy)==lxy)?"Y":"N");
	}
	return 0;
}


