#include <cstdio>
long long read(){
	long long res=0;
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
const int size=100001<<2;
long long sum1[size],sum2[size];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int rsiz,int id){
	sum1[id]=sum1[id<<1]+sum1[id<<1|1];
	sum2[id]=sum2[id<<1]+sum1[id<<1]*rsiz+sum2[id<<1|1];
}
void build(int l,int r,int id){
	if(l==r)sum1[id]=sum2[id]=read();
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(r-m,id);
	}
}
void modify(int l,int r,int id,int x,long long v){
	if(l==r)sum1[id]+=v,sum2[id]+=v;
	else{
		int m=(l+r)>>1;
		if(x<=m)modify(ls,x,v);
		else modify(rs,x,v);
		update(r-m,id);
	}
}
long long query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr) return sum2[id]+sum1[id]*(nr-r);
	else{
		int m=(l+r)>>1;
		long long ans=0;
		if(nl<=m)ans+=query(ls,nl,nr);
		if(m<nr)ans+=query(rs,nl,nr);
		return ans;
	}
}
void printN(long long x){
	if(x>=10)printN(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	if(x<0)x=-x,putchar('-');
	printN(x);
	putchar('\n');
}
int main(){
	int n=read();
	int m=read();
	build(1,n,1);
	long long c,u,v;
	for(int i=0;i<m;++i){
		c=read();
		u=read();
		v=read();
		if(c==1)modify(1,n,1,u,v);
		else print(query(1,n,1,u,v));
	}
	return 0;
}

