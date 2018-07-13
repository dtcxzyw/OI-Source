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
struct Operator{
	int pos,op,p;
	Operator(){}
	Operator(int i,int add,int pri):pos(i),op(add),p(pri){}
	bool operator<(const Operator& rhs) const{
		return pos<rhs.pos;
	}
} A[size<<1];
struct Seg{
	int l,r,cnt;
	long long sum;
} seg[size*40];
int ncnt=1,P[size];
void apply(int l,int r,int& id,int op,int val){
	seg[ncnt++]=seg[id];
	id=ncnt-1;
	seg[id].cnt+=op;
	seg[id].sum+=op*P[val-1];
	if(l!=r){
		int m=(l+r)>>1;
		if(val<=m)apply(l,m,seg[id].l,op,val);
		else apply(m+1,r,seg[id].r,op,val);
	}
}
long long query(int l,int r,int id,int k){
	if(l==r)return static_cast<long long>(k)*P[l-1];
	int cnt=seg[seg[id].l].cnt;
	int m=(l+r)>>1;
	if(cnt>k)return query(l,m,seg[id].l,k);
	else {
		long long res=seg[seg[id].l].sum;
		if(cnt<k)res+=query(m+1,r,seg[id].r,k-cnt);
		return res;
	}
}
int get(int x,int siz){
	return std::lower_bound(P,P+siz,x)-P+1;
}
int root[size];
int main(){
	int m=read();
	int n=read();
	int cnt=0;
	for(int i=0;i<m;++i){
		int b=read();
		int e=read();
		P[i]=read();	
		A[cnt++]=Operator(b,1,P[i]);
		if(e!=n)A[cnt++]=Operator(e+1,-1,P[i]);
	}
	std::sort(A,A+cnt);
	std::sort(P,P+m);
	int siz=std::unique(P,P+m)-P;
	for(int i=1,cp=0;i<=n;++i){
		root[i]=root[i-1];
		while(cp<cnt && A[cp].pos==i){
			apply(1,siz,root[i],A[cp].op,get(A[cp].p,siz));
			++cp;
		}
	}
	long long res=1;
	for(int i=1;i<=n;++i){
		int x=read();
		int a=read();
		int b=read();
		int c=read();
		int k=1+(a*res+b)%c;
		if(seg[root[x]].cnt<=k)res=seg[root[x]].sum;
		else res=query(1,siz,root[x],k);
		printf("%lld\n",res);
	}
	return 0;
}

