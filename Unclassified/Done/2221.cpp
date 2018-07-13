#include <cstdio>
#include <algorithm>
const int size=100001;
typedef unsigned long long sum_t;
sum_t sum1[size<<2|1]={},sum2[size<<2|1],sum3[size<<2|1],lazy[size<<2|1]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void color(int l,int r,int id,sum_t v){
	lazy[id]+=v;
	int len=r-l+1;
	sum_t len2=len*(len+1);
	sum1[id]+=v*len;
	sum2[id]+=v*(len2>>1);
	sum3[id]+=v*(len2*(len<<1|1)/6);
}
void push(int l,int r,int id){
	if(lazy[id]!=0){
		int m=(l+r)>>1;
		color(ls,lazy[id]);
		color(rs,lazy[id]);
		lazy[id]=0;
	}
}
void update(int l,int r,int id){
	sum1[id]=sum1[id<<1]+sum1[id<<1|1];
	int m=(l+r)>>1,lsiz=m-l+1;
	sum2[id]=sum2[id<<1]+sum2[id<<1|1]+sum1[id<<1|1]*lsiz;
	sum3[id]=sum3[id<<1]+sum3[id<<1|1]+lsiz*(sum1[id<<1|1]*lsiz+(sum2[id<<1|1]<<1));
}
void modify(int l,int r,int id,int nl,int nr,int v){
	if(nl<=l&&r<=nr)color(l,r,id,v);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,v);
		if(m<nr)modify(rs,nl,nr,v);
		update(l,r,id);
	}
}
sum_t query2(int l,int r,int id,int nl,int nr){
	if(nl<=l&&r<=nr)return sum2[id]+sum1[id]*(l-nl);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		sum_t ans=0;
		if(nl<=m)ans+=query2(ls,nl,nr); 
		if(m<nr)ans+=query2(rs,nl,nr);
		return ans;
	}
}
sum_t query3(int l,int r,int id,int nl,int nr){
	if(nl<=l&&r<=nr){
		int lsiz=l-nl;
		return sum3[id]+lsiz*(sum1[id]*lsiz+(sum2[id]<<1));
	}else{
		push(l,r,id);
		int m=(l+r)>>1;
		sum_t ans=0;
		if(nl<=m)ans+=query3(ls,nl,nr); 
		if(m<nr)ans+=query3(rs,nl,nr);
		return ans;
	}
}
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
int getCode(){
	int c;
	do c=getchar();
	while(c!='C' && c!='Q');
	return c;
}
sum_t gcd(sum_t a,sum_t b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n,m;
	n=read()-1;
	m=read();
	int c,l,r,v;
	for(int i=0;i<m;++i){
		c=getCode();
		l=read();
		r=read();
		if(c=='C'){
			v=read();
			modify(1,n,1,l,r-1,v);
		}
		else{
			int len=r-l;
			sum_t a=((len+1)*query2(1,n,1,l,r-1)-query3(1,n,1,l,r-1))<<1,b=1ULL*(r-l)*(r-l+1),d;
			d=gcd(a,b);
			a/=d,b/=d;
			printf("%llu/%llu\n",a,b);
		}
	}
	return 0;
}

