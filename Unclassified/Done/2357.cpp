#include <cstdio>
#include <algorithm>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	if(x<0)putchar('-'),x=-x;
	printImpl(x);
	putchar('\n');
}
const int size=200001<<2;
long long off[size]={},sum[size];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int l,int r,int id){
	sum[id]=sum[id<<1]+sum[id<<1|1]+(r-l+1)*off[id];
}
void build(int l,int r,int id){
	if(l==r)sum[id]=read();
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(l,r,id);
	}
}
void modify(int l,int r,int id,int nl,int nr,long long k){
	if(nl<=l && r<=nr)sum[id]+=(r-l+1)*k,off[id]+=k;
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,k);
		if(m<nr)modify(rs,nl,nr,k);
		update(l,r,id);
	}
}
long long query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return sum[id];
	else{
		int m=(l+r)>>1;
		long long res=0;
		if(nl<=m)res+=query(ls,nl,nr);
		if(m<nr)res+=query(rs,nl,nr);
		return res+off[id]*(std::min(nr,r)-std::max(nl,l)+1);
	}
}
int main(){
	int n=read();
	int m=read();
	build(1,n,1);
	long long c,l,r,k;
	for(int i=0;i<m;++i){
		c=read();
		switch(c){
		case 1:{
			l=read();
			r=read();
			k=read();
			modify(1,n,1,l,r,k);
		}break;
		case 2:
		case 3:{
			k=read();
			modify(1,n,1,1,1,(c==2?k:-k));
		}break;
		case 4:{
			l=read();
			r=read();
			print(query(1,n,1,l,r));
		}break;
		case 5:print(query(1,n,1,1,1));break;
		}
	}
	return 0;
}

