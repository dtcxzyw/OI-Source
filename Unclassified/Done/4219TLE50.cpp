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
int getOp(){
	int c;
	do c=getchar();
	while(c!='A' && c!='Q');
	return c;
}
const int size=100005;
int fa[size],siz[size];
void makeRootImpl(int u){
	int p=fa[u];
	if(p!=u){
		makeRootImpl(p);
		fa[p]=u;	
		siz[p]-=siz[u];
		siz[u]+=siz[p];
	}
}
void makeRoot(int u){
	makeRootImpl(u);
	fa[u]=u;
}
int main(){
	int n=read();
	int q=read();
	for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1;
	for(int i=0;i<q;++i){
		int op=getOp();
		int u=read();
		int v=read();
		makeRoot(u);
		if(op=='A'){
			fa[u]=v;
			while(true){
				siz[v]+=siz[u];
				if(v!=fa[v])v=fa[v];
				else break;
			}
		}
		else{
			long long su=siz[u]-siz[v],sv=siz[v];
			printf("%lld\n",su*sv);
		}
	}
	return 0;
}

