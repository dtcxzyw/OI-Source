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
	Int64 val,sum;
} seg[segSiz];
void update(int id){
	seg[id].val=gcd(seg[seg[id].l].val,seg[seg[id].r].val);
	seg[id].sum=seg[seg[id].l].sum+seg[seg[id].r].sum;
}
int cnt=0,root[size],N,M,cx;
Int64 input[2*size];
bool filp=false;
Int64 getVal(int x,int y){
	if(x&&y)return input[filp?y*N+x:x*M+y];
	return 0;
}
#define ls l,m,seg[id].l
#define rs m+1,r,seg[id].r
void build(int l,int r,int& id){
	id=++cnt;
	if(l==r)seg[id].sum=seg[id].val=getVal(cx,l)-getVal(cx,l-1);
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
int bx,ex,by,ey;
Int64 pos,off,res,sum;
void modify(int l,int r,int id){
	if(l==r)seg[id].val+=off;
	else{
		int m=(l+r)>>1;
		if(pos<=m)modify(ls);
		else modify(rs);
		update(id);
	}
}
void query(int l,int r,int id){
	if(by<l && r<=ey)res=gcd(res,seg[id].val);
	else{
		int m=(l+r)>>1;
		if(by<m)query(ls);
		if(m<ey)query(rs);
	}
}
void querySum(int l,int r,int id){
	if(r<=by)sum+=seg[id].sum;
	else{
		int m=(l+r)>>1;
		querySum(ls);
		if(m<by)querySum(rs);
	}
}
int main(){
	N=read();
	M=read();
	int x=read();
	int y=read();
	int t=read();
	for(int i=1;i<=N;++i)
		for(int j=1;j<=M;++j)
			input[i*M+j]=read();
	
	if(N<M){
		filp=true;
		std::swap(N,M);
	}
	
	for(int i=1;i<=N;++i){
		cx=i;
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
			Int64 add=read();
			for(int j=bx;j<=ex;++j){
				pos=by;
				off=add;
				modify(1,M,root[j]);
				pos=ey+1;
				if(pos<=M){
					off=-add;
					modify(1,M,root[j]);
				}
			}
		}
		else{
			res=0;
			for(int j=bx;j<=ex;++j){
				sum=0;
				querySum(1,M,root[j]);
				res=gcd(res,sum);
				query(1,M,root[j]);
			}
			
			printf("%lld\n",(res>0?res:-res));
		}
	}
	return 0;
}

