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
typedef long long Int64;
Int64 iabs(Int64 x){
	return x>=0?x:-x;
}
const int size=300100;
struct Edge{
	int to,next,w;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
Int64 len[size]={},son[size],psum[size];
Int64 calcW(int siz,Int64 x){
	int p=std::lower_bound(son+1,son+siz+1,x)-son;
	//return (x*(p-1)-psum[p-1])+(psum[siz]-psum[p-1]-x*(siz-p+1));
	return psum[siz]-(psum[p-1]<<1)+x*(((p-1)<<1)-siz);
}
Int64 calcMinW(int u){
	int siz=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		son[++siz]=len[v]+E[i].w;
	}
	std::sort(son+1,son+siz+1);
	for(int i=1;i<=siz;++i)
		psum[i]=psum[i-1]+son[i];
	Int64 l=son[1],r=son[siz];
	while(r-l>=3){
		Int64 lm=((l<<1)+r)/3;
		Int64 lw=calcW(siz,lm);
		Int64 rm=(l+(r<<1))/3;
		Int64 rw=calcW(siz,rm);
		if(lw<rw)r=rm;
		else l=lm;
	}
	Int64 cx=0,cw=1LL<<60;
	for(Int64 i=l;i<=r;++i){
		Int64 w=calcW(siz,i);
		if(w<cw)cw=w,cx=i;
	}
	len[u]=cx;
	return cw;
}
Int64 sum=0;
void DFS(int u){
	if(last[u]){
		for(int i=last[u];i;i=E[i].next)
			DFS(E[i].to);
		sum+=calcMinW(u);
	}
}
int main(){
	int n=read()+read();
	for(int i=2;i<=n;++i){
		int p=read();
		int c=read();
		addEdge(p,i,c);
	}
	DFS(1);
	printf("%lld\n",sum);
	return 0;
}

