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
const int size=200005;
struct Node{
	int l,r,val;
} T[size*20];
bool flag[size]={};
int A[size],cur=0,icnt=0;
int build(int l,int r){
	int id=++icnt;
	if(l==r){
		flag[A[l]]=true;
		while(flag[cur])++cur;
		T[id].val=cur;
	}
	else{
		int m=(l+r)>>1;
		T[id].l=build(l,m);
		T[id].r=build(m+1,r);
		T[id].val=std::max(T[T[id].l].val,T[T[id].r].val);
	}
	return id;
}
int nl,nr,val;
int modify(int l,int r,int src){
	if(T[src].val<=val)return src;
	int id=++icnt;
	T[id]=T[src];
	if(nl<=l && r<=nr)T[id].val=val;
	else{
		int m=(l+r)>>1;
		if(nl<=m)T[id].l=modify(l,m,T[id].l);
		if(m<nr)T[id].r=modify(m+1,r,T[id].r);
		T[id].val=std::min(T[id].val,std::max(T[T[id].l].val,T[T[id].r].val));
	}
	return id;
}
int query(int l,int r,int id,int p){
	if(l==r)return T[id].val;
	else{
		int m=(l+r)>>1;
		if(p<=m)return std::min(T[id].val,query(l,m,T[id].l,p));
		return std::min(T[id].val,query(m+1,r,T[id].r,p));
	}
}
int root[size],nxt[size],head[size];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)
		A[i]=std::min(read(),n);
	root[1]=build(1,n);
	for(int i=0;i<=n;++i)head[i]=n+1;
	for(int i=n;i>=1;--i){
		nxt[i]=head[A[i]];
		head[A[i]]=i;
	}
	for(int i=2;i<=n;++i){
		nl=i;
		nr=nxt[i-1]-1;
		val=A[i-1];
		root[i]=modify(1,n,root[i-1]);
	}
	for(int i=0;i<m;++i){
		int l=read();
		int r=read();
		printf("%d\n",query(1,n,root[l],r));
	}
	return 0;
}

