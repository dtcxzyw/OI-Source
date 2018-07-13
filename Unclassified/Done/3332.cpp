#include <cstdio>
#include <cstring>
#include <algorithm>
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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
const int size=50010;
long long sum[size<<2],col[size<<2];
bool clr[size<<2];
void init(){
	clr[1]=true;
	sum[1]=col[1]=0;
}
void color(int l,int r,int id,long long x){
	sum[id]+=(r-l+1)*x;
	col[id]+=x;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void push(int l,int r,int id){
	if(clr[id]){
		sum[id<<1]=sum[id<<1|1]=col[id<<1]=col[id<<1|1]=0;
		clr[id<<1]=clr[id<<1|1]=true;
		clr[id]=false;
	}
	if(col[id]){
		int m=(l+r)>>1;
		color(ls,col[id]);
		color(rs,col[id]);
		col[id]=0;
	}
}
void modify(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)color(l,r,id,1);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr);
		if(m<nr)modify(rs,nl,nr);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
long long query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return sum[id];
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		long long res=0;
		if(nl<=m)res+=query(ls,nl,nr);
		if(m<nr)res+=query(rs,nl,nr);
		return res;
	}
}
struct Query{
	int op,l,r,id,mark;
	long long c;
	bool operator<(const Query& rhs) const{
		return mark==rhs.mark?id<rhs.id:mark<rhs.mark;
	}
} Q[size];
int n,res[size];
void foo(int l,int r,int b,int e){
	if(l==r){
		for(int i=b;i<e;++i)
			if(Q[i].op==2)
				res[Q[i].id]=l;
	}
	else if(l<r){
		int mid=(l+r)>>1,cnt=0;
		init();
		for(int i=b;i<e;++i){
			if(Q[i].op==1){
				if(Q[i].c>mid)modify(1,n,1,Q[i].l,Q[i].r),Q[i].mark=1;
				else Q[i].mark=0,++cnt;
			}
			else{
				long long s=query(1,n,1,Q[i].l,Q[i].r);
				if(Q[i].c<=s)Q[i].mark=1;
				else Q[i].c-=s,Q[i].mark=0,++cnt;
			}
		}
		std::sort(Q+b,Q+e);
		foo(l,mid,b,b+cnt);
		foo(mid+1,r,b+cnt,e);
	}
}
int main(){
	n=read();
	int m=read();
	for(int i=0;i<m;++i){
		Q[i].op=read();
		Q[i].l=read();
		Q[i].r=read();
		Q[i].c=read();
		Q[i].id=i;
	}
	memset(res,0x3f,sizeof(res));
	foo(-n,n,0,m);
	for(int i=0;i<m;++i)
		if(res[i]!=0x3f3f3f3f)
			print(res[i]);
	return 0;
}

