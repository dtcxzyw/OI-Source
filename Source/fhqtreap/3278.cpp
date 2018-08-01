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
	int res=0,c;
	do c=getchar();
	while(c<'a'||c>'z');
	while('a'<=c&&c<='z'){
		res=c;
		c=getchar();
	}
	return res;
}
int getRand(){
	static int seed=346;
	return seed=seed*48271LL%2147483647;
}
const int size=300050,mod=20130426;
typedef long long Int64;
struct Node{
	int val,pri,fac,off,siz,ls,rs;
} T[size];
int newNode(){
	static int cnt=0;
	int id=++cnt;
	T[id].val=0;
	T[id].pri=getRand();
	T[id].fac=1,T[id].off=0;
	T[id].siz=1;
	T[id].ls=T[id].rs=0;
	return id;
}
void add(int u,int k){
	Node& node=T[u];
	node.val=(node.val+k)%mod;
	node.off=(node.off+k)%mod;
}
void mul(int u,Int64 k){
	Node& node=T[u];
	node.val=node.val*k%mod;
	node.off=node.off*k%mod;
	node.fac=node.fac*k%mod;
}
void push(int u){
	Node& node=T[u];
	if(node.fac!=1){
		if(node.ls)mul(node.ls,node.fac);
		if(node.rs)mul(node.rs,node.fac);
		node.fac=1;
	}
	if(node.off){
		if(node.ls)add(node.ls,node.off);
		if(node.rs)add(node.rs,node.off);
		node.off=0;
	}
}
void update(int u){
	T[u].siz=T[T[u].ls].siz+T[T[u].rs].siz+1;
}
int merge(int x,int y){
	if(x&&y){
		push(x);
		push(y);
		if(T[x].pri<T[y].pri){
			T[x].rs=merge(T[x].rs,y);
			update(x);
			return x;
		}
		else{
			T[y].ls=merge(x,T[y].ls);
			update(y);
			return y;
		}
	}
	return x|y;
}
void split(int u,int k,int& x,int& y){
	if(u){
		push(u);
		int lsiz=T[T[u].ls].siz;
		if(k<=lsiz){
			y=u;
			split(T[u].ls,k,x,T[u].ls);
		}
		else{
			x=u;
			split(T[u].rs,k-lsiz-1,T[u].rs,y);
		}
		update(u);
	}
	else x=y=0;
}
int build(int l,int r){
	if(l<=r){
		int m=(l+r)>>1;
		int u=newNode();
		T[u].ls=build(l,m-1);
		T[u].rs=build(m+1,r);
		update(u);
		return u;
	}
	return 0;
}
Int64 x;
int DFS(int u,int cur){
	if(u){
		push(u);
		return DFS(T[u].ls,(DFS(T[u].rs,cur)*x+T[u].val)%mod);
	}
	return cur;
}
int sum(int u){
	if(u){
		push(u);
		return sum(T[u].ls)+T[u].val+sum(T[u].rs);
	}
	return 0;
}
void print(int u,int cnt=0){
	if(u){
		push(u);
		print(T[u].ls,cnt);
		if(T[u].val)printf("+%d*x^%d",T[u].val,T[T[u].ls].siz+cnt);
		return print(T[u].rs,cnt+T[T[u].ls].siz+1);
	}
}
int main(){
	int n=read();
	int root=build(0,100000);
	for(int i=0;i<n;++i){
		switch(getOp()){
			case 'l':{
				int l=read();
				int r=read();
				int lt=0,rt=0,llt=0,lrt=0;
				split(root,r+1,lt,rt);
				split(lt,l,llt,lrt);
				mul(lrt,read());
				root=merge(merge(llt,lrt),rt);
				break;
			}
			case 'd':{
				int l=read();
				int r=read();
				int lt=0,rt=0,llt=0,lrt=0;
				split(root,r+1,lt,rt);
				split(lt,l,llt,lrt);
				add(lrt,read());
				root=merge(merge(llt,lrt),rt);
				break;
			}
			case 'x':{
				int l=read();
				int r=read();
				int p1=0,p2=0,p3=0,p4=0,t1=0,t2=0;
				split(root,r+2,t1,p4);
				split(t1,r,t2,p3);
				split(t2,l,p1,p2);
				T[p3].val=sum(p3)%mod;
				T[p3].ls=T[p3].rs=0;
				T[p3].siz=1;
				root=merge(merge(merge(p1,newNode()),p2),merge(p3,p4));
				break;
			}
			case 'y':{
				x=read();
				printf("%d\n",DFS(root,0));
				break;
			}
		}
	}
	return 0;
}

