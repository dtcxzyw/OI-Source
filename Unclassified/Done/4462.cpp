#include <cstdio>
#include <cmath>
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
const int size=100005;
int A[size],L[size]={},R[size]={},bid[size],k;
long long cur=0;
void insertL(int x){
	int lval=A[x-1],rval=A[x];
	++L[lval];
	++R[rval];
	cur+=R[lval^k];
}
void eraseL(int x){
	int lval=A[x-1],rval=A[x];
	cur-=R[lval^k];
	--L[lval];
	--R[rval];
}
void insertR(int x){
	int lval=A[x-1],rval=A[x];
	++L[lval];
	++R[rval];
	cur+=L[rval^k];
}
void eraseR(int x){
	int lval=A[x-1],rval=A[x];
	cur-=L[rval^k];
	--L[lval];
	--R[rval];
}
struct Query{
	int l,r,id;
	bool operator<(const Query& rhs) const{
		return bid[l]==bid[rhs.l]?r<rhs.r:l<rhs.l;
	}
} Q[size];
long long ans[size];
int main(){
	int n=read();
	int bsiz=sqrt(n)+1;
	for(int i=1;i<=n;++i)bid[i]=i/bsiz;
	int m=read();
	k=read();
	A[0]=0;
	for(int i=1;i<=n;++i)
		A[i]=A[i-1]^read();
	for(int i=0;i<m;++i){
		Q[i].l=read();
		Q[i].r=read();
		Q[i].id=i;
	}
	std::sort(Q,Q+m);
	int l=1,r=0;
	for(int i=0;i<m;++i){
		while(r<Q[i].r)insertR(++r);
		while(r>Q[i].r)eraseR(r--);
		while(l<Q[i].l)eraseL(l++);
		while(l>Q[i].l)insertL(--l);
		ans[Q[i].id]=cur;
	}
	for(int i=0;i<m;++i)
		printf("%lld\n",ans[i]);
	return 0;
}

