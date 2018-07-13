#include <cstdio>
#include <algorithm>
typedef long long Int64;
Int64 read(){
	Int64 res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
#define asInt64(x) static_cast<Int64>(x)
const int size=100005;
struct Node{
	int l,r;
	Int64 g,siz;
} T[size*20];
int root[size]={},icnt=0;
int insert(int l,int r,int src,int p,int siz){
	int id=++icnt;
	T[id]=T[src];
	T[id].g+=asInt64(p)*siz;
	T[id].siz+=siz;
	if(l!=r){
		int m=(l+r)>>1;
		if(p<=m)T[id].l=insert(l,m,T[id].l,p,siz);
		else T[id].r=insert(m+1,r,T[id].r,p,siz);
	}
	return id;
}
Int64 query(int l,int r,int id,Int64 siz){
	if(l==r)return siz*l;
	Int64 lsiz=T[T[id].l].siz;
	if(lsiz==siz)return T[T[id].l].g;
	int m=(l+r)>>1;
	if(lsiz>siz)return query(l,m,T[id].l,siz);
	return T[T[id].l].g+query(m+1,r,T[id].r,siz-lsiz);
}
struct Info{
	int d,p,l;
	bool operator<(const Info& rhs) const{
		return d<rhs.d;	
	}
} A[size];
int main(){
	int n=read();
	int m=read();
	int maxp=0;
	for(int i=0;i<n;++i){
		A[i].d=read();
		A[i].p=read();
		maxp=std::max(maxp,A[i].p);
		A[i].l=read();
	}
	std::sort(A,A+n);
	int cur=n-1;
	for(int i=A[n-1].d;i>=1;--i){
		root[i]=root[i+1];
		while(cur>=0 && A[cur].d==i){
			root[i]=insert(1,maxp,root[i],A[cur].p,A[cur].l);
			--cur;
		}
	}
	for(int i=0;i<m;++i){
		Int64 g=read();
		Int64 siz=read();
		int l=1,r=A[n-1].d,ans=-1;
		while(l<=r){
			int m=(l+r)>>1;
			if(T[root[m]].siz>=siz && query(1,maxp,root[m],siz)<=g)l=m+1,ans=m;
			else r=m-1;
		}
		printf("%d\n",ans);	
	}
	return 0;
}

