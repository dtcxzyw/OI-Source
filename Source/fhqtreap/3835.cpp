#include <cstdio>
#include <algorithm>
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
int getRand(){
	static int seed=4235;
	return seed=seed*48271LL%2147483647;
}
const int size=500005;
struct Node{
	int val,pri,ls,rs,siz;
} T[size*20];
int icnt=0;
int newNode(int val){
	int id=++icnt;
	T[id].val=val;
	T[id].pri=getRand();
	T[id].ls=T[id].rs=0;
	T[id].siz=1;
	return id;
}
bool disableClone=true;
int clone(int u){
	if(disableClone)return u;
	int id=++icnt;
	T[id]=T[u];
	return id;
}
void update(int u){
	T[u].siz=T[T[u].ls].siz+T[T[u].rs].siz+1;
}
void split(int u,int k,int& x,int& y){
	if(u){
		if(T[u].val<=k){
			x=clone(u);
			split(T[x].rs,k,T[x].rs,y);
			update(x);
		}
		else{
			y=clone(u);
			split(T[y].ls,k,x,T[y].ls);
			update(y);
		}
	}
	else x=y=0;
}
int merge(int x,int y){
	if(x && y){
		if(T[x].pri<T[y].pri){
			x=clone(x);
			T[x].rs=merge(T[x].rs,y);
			update(x);
			return x;
		}
		else{
			y=clone(y);
			T[y].ls=merge(x,T[y].ls);
			update(y);
			return y;
		}
	}
	return x|y;
}
int root[size]={};
int insert(int src,int val){
	int lt=0,rt=0;
	disableClone=false;
	split(src,val,lt,rt);
	disableClone=true;
	return merge(lt,merge(newNode(val),rt));
}
int del(int src,int val){
	int lt=0,rt=0,llt=0,lrt=0;
	disableClone=false;
	split(src,val,lt,rt);
	disableClone=true;
	split(lt,val-1,llt,lrt);
	if(lrt)lrt=merge(T[lrt].ls,T[lrt].rs);
	return merge(llt,merge(lrt,rt));
}
int kthImpl(int u,int val){
	if(u){
		if(T[u].val<val)return T[T[u].ls].siz+1+kthImpl(T[u].rs,val);
		return kthImpl(T[u].ls,val);
	}
	return 0;
}
int kth(int root,int val){
	printf("%d\n",kthImpl(root,val)+1);
	return root;
}
int findImpl(int u,int k){
	int lsiz=T[T[u].ls].siz;
	if(k<=lsiz)return findImpl(T[u].ls,k);
	if(k==lsiz+1)return T[u].val;
	return findImpl(T[u].rs,k-lsiz-1);
}
int find(int root,int k){
	printf("%d\n",findImpl(root,k));
	return root;
}
const int fail=2147483647;
int prevImpl(int u,int val){
	if(u){
		if(T[u].val<val)return std::max(T[u].val,prevImpl(T[u].rs,val));
		return prevImpl(T[u].ls,val);
	}
	return -fail;
}
int prev(int root,int val){
	printf("%d\n",prevImpl(root,val));
	return root;
}
int nextImpl(int u,int val){
	if(u){
		if(T[u].val>val)return std::min(T[u].val,nextImpl(T[u].ls,val));
		return nextImpl(T[u].rs,val);
	}
	return fail;
}
int next(int root,int val){
	printf("%d\n",nextImpl(root,val));
	return root;
}
typedef int(*Func)(int root,int val);
int main(){
	int n=read();
	Func func[7]={0,insert,del,kth,find,prev,next};
	for(int i=1;i<=n;++i){
		int cur=root[read()];
		int op=read();
		int val=read();
		root[i]=func[op](cur,val);
	}
	return 0;
}

