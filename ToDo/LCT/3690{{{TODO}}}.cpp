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
int getRand(){
	static int seed=3523;
	return seed=seed*42871LL%2147483647;
}
const int size=300005;
struct Node{
	int p,val,sv,ls,rs,pri,lazy;
	bool rev,root;
} T[size];
void color(int u,int mask){
	T[u].val^=mask;
	T[u].lazy^=mask;
}
void push(int u){
	if(T[u].rev){
		T[u].rev=false;
		std::swap(T[u].ls,T[u].rs);
		if(T[u].ls)T[T[u].ls].rev^=1;
		if(T[u].rs)T[T[u].rs].rev^=1;
	}
	if(T[u].lazy){
		if(T[u].ls)color(T[u].ls,T[u].lazy);
		if(T[u].rs)color(T[u].rs,T[u].lazy);
		T[u].lazy=0;
	}
}
void update(int u){}
int merge(int u,int v){
	if(u && v){
		if(T[u].pri<T[v].pri){
			push(u);
			T[u].rs=merge(T[u].rs,v);
			update(u);
			return u;
		}
		else{
			push(v);
			T[v].ls=merge(u,T[v].ls);
			update(v);
			return v;
		}
	}
	return u|v;
}
int getRoot(int u){
	while(!T[u].root)u=T[u].p;
	return u;
}
bool st[size];
int top;
void DFS(int u,int& a,int& b){
	if(u){
		if(st[top--]){
			a=merge(a,T[u].ls);
			
		}
		else{
			
		}
	}
}
void split(int u,int& a,int& b){
	int top=0;
	while(!T[u].root){
		st[++top]=T[T[u].fa].rs==u;
		u=T[u].fa;
	}
	DFS(u,a,b);
}
void access(int u){
	int a=0,b=0;
	split(u,a,b);
	
}
void makeRoot(int u){
	
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		T[i].p=0;
		T[i].val=T[i].sv=read();
		T[i].ls=T[i].rs=0;
		T[i].pri=getRand();
		T[i].lazy=0;
		T[i].rev=false;
		T[i].root=true;
	}
	for(int i=0;i<m;++i){
		int op=read();
		int u=read();
		int v=read();
		switch(op){
			case 0:{
				makeRoot(u);
				access(v);

				break;
			}
			case 1:{
				if(getRoot(u)!=getRoot(v)){
					makeRoot(u);
					access(v);
					
				}
				break;
			}
			case 2:{
				makeRoot(u);
				access(v);
				!!!
				break;
			}
			case 3:{
				int mask=T[u].sv^v;
				T[u].sv=v;
				color(u,mask);
				break;
			}
		}
	}
	return 0;
}

