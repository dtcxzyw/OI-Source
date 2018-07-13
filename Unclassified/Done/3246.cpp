#include <cstdio>
#include <algorithm>
#include <cmath>
typedef long long Int64;
Int64 read(){
	Int64 res=0;
	int c;
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
void printImpl(Int64 x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(Int64 x){
	if(x<0)putchar('-'),x=-x;
	printImpl(x);
	putchar('\n');
}
const Int64 size=1000010;
Int64 A[size],mip[size][20],lg[size];//[i,i+(1<<k))
Int64 minv(Int64 a,Int64 b){
	return A[a]<A[b]?a:b;
}
Int64 query(Int64 l,Int64 r){
	Int64 d=lg[r-l+1];
	return minv(mip[l][d],mip[r+1-(1<<d)][d]);
}
Int64 fl[size],fr[size];
Int64 sta[size],top;
void pre(Int64 n,Int64* f){
	f[0]=0,top=1,sta[1]=0,A[0]=-(1LL<<60);
	for(Int64 i=1;i<=n;++i){
		while(A[sta[top]]>A[i])--top;
		f[i]=f[sta[top]]+(i-sta[top])*A[i];
		sta[++top]=i;
	}
}
Int64 calcL(Int64 l,Int64 r){
	Int64 p=query(l-1,r);
	return A[p]*(r-p+1)+fr[l-1]-fr[p];
}
Int64 calcR(Int64 l,Int64 r){
	Int64 p=query(l,r+1);
	return A[p]*(p-l+1)+fl[r+1]-fl[p];
}
Int64 bid[size];
struct Query{
	Int64 l,r,id;
	bool operator<(const Query& rhs) const{
		return bid[l]==bid[rhs.l]?r<rhs.r:bid[l]<bid[rhs.l];
	}
} Q[size];
Int64 res[size];
int main(){
	Int64 n=read();
	Int64 q=read();
	lg[1]=0;
	for(Int64 i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	Int64 block=sqrt(n)+1;
	for(Int64 i=1;i<=n;++i)A[i]=read(),mip[i][0]=i,bid[i]=i/block;
	for(Int64 k=1;k<20;++k)
		for(Int64 i=1;i<=n;++i)
			if(i+(1<<(k-1))<=n)
				mip[i][k]=minv(mip[i][k-1],mip[i+(1<<(k-1))][k-1]);
			else
				mip[i][k]=mip[i][k-1];
	pre(n,fl);
	std::reverse(A+1,A+n+1);
	pre(n,fr);
	std::reverse(A+1,A+n+1);
	std::reverse(fr+1,fr+n+1);
	for(Int64 i=0;i<q;++i){
		Q[i].l=read();
		Q[i].r=read();
		Q[i].id=i;
	}
	std::sort(Q,Q+q);
	Int64 nl=1,nr=1;
	Int64 ans=A[1];
	for(Int64 i=0;i<q;++i){
		while(nr<Q[i].r)ans+=calcR(nl,nr++);
		while(nr>Q[i].r)ans-=calcR(nl,--nr);
		while(nl>Q[i].l)ans+=calcL(nl--,nr);
		while(nl<Q[i].l)ans-=calcL(++nl,nr);
		res[Q[i].id]=ans;
	}
	for(Int64 i=0;i<q;++i)
		print(res[i]);
	return 0;	
}

