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
const int size=300005;
int w[size],fa[size];
int find(int u){
	return fa[u]==u?u:find(fa[u]);
}
void makeRootImpl(int u){
	if(fa[u]!=u)makeRootImpl(fa[u]);
	fa[fa[u]]=u;
}
void makeRoot(int u){
	makeRootImpl(u);
	fa[u]=u;
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=1;i<=n;++i)w[i]=read();
	for(int i=0;i<m;++i){
		switch(read()){
			case 0:{
				int u=read(),v=read();
				makeRoot(u);
				int res=w[u];
				while(u!=v){
					res^=w[v];
					v=fa[v];
				}
				printf("%d\n",res);
			}break;
			case 1:{
				int u=read(),v=read();
				if(find(u)!=find(v)){
					makeRoot(u);
					fa[u]=v;
				}
			}break;
			case 2:{
				int u=read();
				int v=read();
				if(find(u)==find(v)){
					makeRoot(u);
					fa[v]=v;
				}
			}break;
			case 3:{
				int u=read();
				w[u]=read();
			}break;
		}
	}
	return 0;
}

