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
const int size=100100;
struct Node{
	int key,p,c[2],size;
	bool rev;
} T[size];
int cnt=0;
#define root T[0].c[1]
int son(int p,int u){
	return T[p].c[1]==u;
}
void update(int u){
	T[u].size=T[T[u].c[0]].size+T[T[u].c[1]].size+1;
}
void push(int u){
	if(u && T[u].rev){
		T[T[u].c[0]].rev^=1;
		T[T[u].c[1]].rev^=1;
		T[u].rev=false;
		std::swap(T[u].c[0],T[u].c[1]);
	}
}
void connect(int u,int p,int x){
	T[p].c[x]=u;
	T[u].p=p;
}
void rotate(int u){
	int p=T[u].p;
	int sp=son(p,u);
	int pp=T[p].p;
	int spp=son(pp,p);
	connect(T[u].c[sp^1],p,sp);
	connect(p,u,sp^1);
	connect(u,pp,spp);
	update(p);
	update(u);
}
void splay(int u,int end){
	push(u);
	end=T[end].p;
	while(T[u].p!=end){
		int p=T[u].p;
		int pp=T[p].p;
		push(pp);
		push(p);
		push(u);
		if(end!=pp)rotate(son(pp,p)==son(p,u)?p:u);
		rotate(u);
	}
}
int n;
void print(int u){
	push(u);
	if(T[u].c[0])print(T[u].c[0]);
	if(T[u].key>=1 && T[u].key<=n)
		printf("%d ",T[u].key);
	if(T[u].c[1])print(T[u].c[1]);
}
void build(int l,int r,int& u,int p){
	if(l>r)return;
	u=++cnt;
	int m=(l+r)>>1;
	T[u].key=m;
	T[u].rev=false;
	T[u].size=1;
	T[u].p=p;
	if(l!=r){
		build(l,m-1,T[u].c[0],u);
		build(m+1,r,T[u].c[1],u);
		T[u].size+=T[T[u].c[0]].size+T[T[u].c[1]].size;
	}
}
int getKth(int u,int x){
	push(u);
	int lsiz=T[T[u].c[0]].size;
	if(lsiz+1==x)return u;
	if(x<=lsiz)return getKth(T[u].c[0],x);
	else return getKth(T[u].c[1],x-lsiz-1);
}
int main(){
	n=read();
	build(0,n+1,root,0);
	int m=read();
	for(int i=0;i<m;++i){
		int l=read();
		int r=read();
		if(l!=r){
			splay(getKth(root,l),root);
			splay(getKth(root,r+2),T[root].c[1]);
			T[T[T[root].c[1]].c[0]].rev^=1;
		}
	}
	print(root);
	return 0;
}

