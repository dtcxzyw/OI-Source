#include <cstdio>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100100;
struct Node{
	int key,p,size,c[2],cnt;
} T[size];
#define root T[0].c[1]
int cnt=0,siz=0;
int son(int p,int u){
	return T[p].c[1]==u;
}
void update(int u){
	T[u].size=T[T[u].c[0]].size+T[T[u].c[1]].size+T[u].cnt;
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
	end=T[end].p;
	while(T[u].p!=end){
		int p=T[u].p;
		int pp=T[p].p;
		if(end!=pp)rotate(son(pp,p)==son(p,u)?p:u);
		rotate(u);
	}
}
int find(int x){
	int u=root;
	while(true){
		if(T[u].key==x){
			splay(u,root);
			return u;
		}
		int son=x>=T[u].key;
		if(T[u].c[son])u=T[u].c[son];
		else break;
	}
	return 0;
}
int newNode(int x,int p){
	int u=++cnt;++siz;
	T[u].key=x,T[u].size=T[u].cnt=1,T[u].p=p,T[u].c[0]=T[u].c[1]=0;
	return u;
}
int insert(int x){
	if(siz){
		int p=root;
		while(true){
			++T[p].size;
			if(T[p].key==x){
				++T[p].cnt;
				return p;	
			}
			int son=x>=T[p].key;
			if(T[p].c[son])p=T[p].c[son];
			else return T[p].c[son]=newNode(x,p);
		}
	}
	else{
		root=newNode(x,0);
		return 0;
	}
}
void erase(int x){
	int u=find(x);
	if(!u)return;
	if(T[u].cnt>1){
		--T[u].cnt;
		--T[u].size;
	}
	else{
		--siz;
		if(T[u].c[0]){
			int lc=T[u].c[0];
			while(T[lc].c[1])lc=T[lc].c[1];
			splay(lc,T[u].c[0]);
			int rc=T[u].c[1];
			connect(rc,lc,1);
			connect(lc,0,1);
			update(lc);
		}
		else{
			root=T[u].c[1];
			T[root].p=0;
		}
	}
}
int findKth(int x){
	int res=0,u=root;
	while(u){
		if(T[u].key==x){
			res+=T[T[u].c[0]].size+1;
			break;
		}
		if(x<T[u].key)u=T[u].c[0];
		else{
			res+=T[T[u].c[0]].size+T[u].cnt;
			u=T[u].c[1];
		}
	}
	if(u)splay(u,root);
	else res=0;
	return res;
}
int getKth(int x){
	int p=root;
	while(true){
		int csiz=T[T[p].c[0]].size;
		if(x<=csiz)p=T[p].c[0];
		else{
			csiz+=T[p].cnt;
			if(x<=csiz)break;
			else{
				x-=csiz;
				p=T[p].c[1];
			}
		}
	}
	splay(p,root);
	return T[p].key;
}
int prev(int x){
	int u=root,res=-(1<<30);
	while(u){
		if(T[u].key<x && T[u].key>res)res=T[u].key;
		u=T[u].c[x>T[u].key];
	}
	return res;
}
int next(int x){
	int u=root,res=1<<30;
	while(u){
		if(T[u].key>x && T[u].key<res)res=T[u].key;
		u=T[u].c[x>=T[u].key];
	}
	return res;
}
int main(){
	int n=read();
	for(int i=0;i<n;++i)
		switch(read()){
			case 1:splay(insert(read()),root);break;
			case 2:erase(read());break;
			case 3:printf("%d\n",findKth(read()));break;
			case 4:printf("%d\n",getKth(read()));break;
			case 5:printf("%d\n",prev(read()));break;
			case 6:printf("%d\n",next(read()));break;
		}
	return 0;
}

