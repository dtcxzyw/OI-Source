#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long Int64;
Int64 read(){
	Int64 res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
struct XorBase{
	Int64 b[64];
	XorBase(){
		memset(b,0,sizeof(XorBase));
	}
	void push(Int64 x){
		for(int i=60;i>=0;--i)
			if(x&(1LL<<i)){
				if(b[i])x^=b[i];
				else{
					b[i]=x;
					return;
				}
			}
	}
	Int64 calcVal() const{
		Int64 res=0;
		for(int i=60;i>=0;--i)
			res=std::max(res,res^b[i]);
		return res;
	}
};
XorBase merge(const XorBase& a,const XorBase& b){
	XorBase res=a;
	for(int i=0;i<=60;++i)
		if(b.b[i])
			res.push(b.b[i]);
	return res;
}
const int size=20010;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
XorBase base[size][17];
int p[size][17],d[size]={};
void DFS(int u){
	for(int i=1;i<17;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=1;i<17;++i)
		base[u][i]=merge(base[p[u][i-1]][i-1],base[u][i-1]);
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			d[v]=d[u]+1;
			p[v][0]=u;
			DFS(v);
		}
	}
}
Int64 query(int u,int v){
	if(d[u]<d[v])std::swap(u,v);
	XorBase res;
	int delta=d[u]-d[v];
	for(int i=0;i<17;++i)
		if(delta&(1<<i)){
			res=merge(res,base[u][i]);
			u=p[u][i];
		}
	for(int i=16;i>=0;--i)
		if(p[u][i]!=p[v][i]){
			res=merge(res,merge(base[u][i],base[v][i]));
			u=p[u][i];
			v=p[v][i];	
		}
	if(u!=v)res=merge(res,merge(base[u][1],base[v][1]));
	else res=merge(res,base[u][0]);
	return res.calcVal();
}
int main(){
	int n=read();
	int q=read();
	for(int i=1;i<=n;++i)
		base[i][0].push(read());
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=1;
	DFS(1);
	for(int i=0;i<q;++i)
		printf("%lld\n",query(read(),read()));
	return 0;
}

