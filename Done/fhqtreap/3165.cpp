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
	static int seed=321;
	return seed=seed*48271LL%2147483647;
}
const int size=100005;
struct Node{
	int val,pri,ls,rs,siz,minv;
	bool rev;
} T[size];
int newNode(int x){
	static int cnt=0;
	int id=++cnt;
	T[id].val=x;
	T[id].pri=getRand();
	T[id].rev=false;
	T[id].ls=T[id].rs=0;
	T[id].siz=1;
	T[id].minv=x;
	return id;
}
void update(int u){
	T[u].siz=T[T[u].ls].siz+T[T[u].rs].siz+1;
	T[u].minv=std::min(T[u].val,std::min(T[T[u].ls].minv,T[T[u].rs].minv));
}
void push(int u){
	if(u && T[u].rev){
		T[u].rev=false;
		std::swap(T[u].ls,T[u].rs);
		if(T[u].ls)T[T[u].ls].rev^=1;
		if(T[u].rs)T[T[u].rs].rev^=1;
	}
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
int merge(int x,int y){
	if(x && y){
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
std::pair<int,int> A[size];
int build(int l,int r){
	if(l<=r){
		int m=(l+r)>>1;
		int id=newNode(A[m].second);
		T[id].ls=build(l,m-1);
		T[id].rs=build(m+1,r);
		update(id);
		return id;
	}
	return 0;
}
int find(int u,int x){
	push(u);
	if(T[u].val==x)return T[T[u].ls].siz+1;
	if(T[u].ls && T[T[u].ls].minv==x)return find(T[u].ls,x);
	else return T[T[u].ls].siz+1+find(T[u].rs,x);
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i)A[i]=std::make_pair(read(),i);
	std::sort(A+1,A+n+1);
	for(int i=1;i<=n;++i)A[i]=std::make_pair(A[i].second,i);
	std::sort(A+1,A+n+1);
	T[0].minv=n+1;
	int root=build(1,n);
	for(int i=1;i<=n;++i){
		int p=find(root,T[root].minv);
		printf("%d ",p+i-1);
		int lt=0,rt=0;
		if(p!=n-i+1)split(root,p,lt,rt);
		else lt=root;
		T[lt].rev^=1;
		if(i!=n){
			int llt=0,lrt=0;
			split(lt,1,llt,lrt);
			root=merge(lrt,rt);
		}
	}
	return 0;
}

