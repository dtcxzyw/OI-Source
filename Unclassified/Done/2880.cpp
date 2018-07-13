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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
struct Range{
	int l,r;
	Range():l(1<<30),r(0){}
	Range(int v):l(v),r(v){}
	void operator&=(Range rhs){
		if(rhs.l<l)l=rhs.l;
		if(rhs.r>r)r=rhs.r;
	}
	void print() const{
		printImpl(r-l);
		putchar('\n');
	}
};
const int size=50001<<2;
Range val[size];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)val[id]=read();
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		val[id]&=val[id<<1];
		val[id]&=val[id<<1|1];
	}
}
int nl,nr;
Range res;
void query(int l,int r,int id){
	if(nl<=l && r<=nr)res&=val[id];
	else{
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
int main(){
	int n=read();
	int q=read();
	build(1,n,1);
	for(int i=0;i<q;++i){
		nl=read();
		nr=read();
		res=Range();
		query(1,n,1);
		res.print();
	}	
	return 0;
}

