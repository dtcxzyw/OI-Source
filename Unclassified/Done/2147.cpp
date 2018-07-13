#include <cstdio>
#include <cctype>
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
int getCode(){
	int c,res;
	do c=getchar();
	while(!isalpha(c));
	res=c;
	while(isalpha(c))c=getchar();
	return res;
}
const int size=10001;
int fa[size];
void inv(int x){
	if(fa[x]!=x){
		int p=fa[x];
		inv(p);
		fa[p]=x;
	}
}
void makeRoot(int x){
	inv(x);
	fa[x]=x;
}
int find(int u){
	while(u!=fa[u])u=fa[u];
	return u;
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=0;i<m;++i){
		int op=getCode();
		int u=read();
		int v=read();
		makeRoot(u);
		if(op=='Q')puts(u==find(v)?"Yes":"No");
		else if(op=='C')fa[u]=v;
		else if(op=='D')fa[v]=v;
	}
	return 0;
}

