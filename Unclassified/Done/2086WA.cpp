#include <cstdio>
#include <algorithm>
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
Int64 gcd(Int64 a,Int64 b){
	return b?gcd(b,a%b):a;
}
const int size=500100,segSiz=size*20;
struct Seg{
	bool flag;
	int l,r;
	Int64 val,lazy;
} seg[segSiz];
void update(int id){
	seg[id].val=gcd(seg[seg[id].l].val,seg[seg[id].r].val);
}
int cnt=0,root[size],N,M,cx;
Int64 input[size];
bool filp=false;
#define ls l,m,seg[id].l
#define rs m+1,r,seg[id].r
void build(int l,int r,int& id){
	id=++cnt;
	if(l==r){
		int pos=(filp?(l-1)*N+cx:cx*M+l-1);
		seg[id].val=input[pos]; 
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
int bx,ex,by,ey;
Int64 off,res;
void color(int id){
	if(seg[id].l)seg[id].lazy+=off,seg[id].flag=true;
	else seg[id].val+=off;
}
void push(int id){
	if(seg[id].lazy!=0){
		color(seg[id].l);
		color(seg[id].r);
		seg[id].lazy=0;
	}
}
void modify(int l,int r,int id){
	if(by<=l && r<=ey)color(id);
	else{
		int m=(l+r)>>1;
		if(by<=m)modify(ls);
		if(m<ey)modify(rs);
	}
}
void calc(int id){
	if(seg[id].flag){
		push(id);
		calc(seg[id].l);
		calc(seg[id].r);
		update(id);
		seg[id].flag=false;
	}
}
void query(int l,int r,int id){
	if(by<=l && r<=ey){
		calc(id);
		res=gcd(res,seg[id].val);
	}
	else{
		push(id);
		int m=(l+r)>>1;
		if(by<=m)query(ls);
		if(m<ey)query(rs);
	}
}
int main(){
	N=read();
	M=read();
	int x=read();
	int y=read();
	int t=read();
	for(int i=0;i<N;++i)
		for(int j=0;j<M;++j)
			input[i*M+j]=read();
	
	if(N<M){
		filp=true;
		std::swap(N,M);
	}
	
	for(int i=1;i<=N;++i){
		cx=i-1;
		build(1,M,root[i]);
	}
	
	for(int i=0;i<t;++i){
		int op=read();
		if(op){
			bx=read();
			by=read();
			ex=read();
			ey=read();
		}
		else{
			bx=x-read();
			by=y-read();
			ex=x+read();
			ey=y+read();
		}
		
		if(filp){
			std::swap(bx,by);
			std::swap(ex,ey);	
		}
		
		if(op){
			off=read();
			for(int j=bx;j<=ex;++j)modify(1,M,root[j]);
		}
		else{
			res=0;
			for(int j=bx;j<=ex;++j)query(1,M,root[j]);
			printf("%lld\n",res);
		}
	}
	return 0;
}

