#include <cstdio>
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
Int64 iabs(Int64 a){
	return a>0?a:-a;
}
Int64 gcd(Int64 a,Int64 b){
	return b?gcd(b,a%b):iabs(a);
}
const int size=500100;
Int64 pool[size*50];
Int64* alloc(int siz){
	static int cnt=0;
	Int64* p=pool+cnt;
	cnt+=siz;
	return p;
}
int N,M;
Int64 A[size],input[2*size];
Int64 getVal(int x,int y){
	if(x&&y)return input[x*M+y];
	return 0;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
Int64 nl1,nr1,res,off,py;
struct Seg1D {
	Int64* val;
	Seg1D(int size){
		val=alloc((size+10)<<2);
	}
	Seg1D(){}
	void update(int id){
		val[id]=gcd(val[id<<1],val[id<<1|1]);
	}
	void build(int l,int r,int id){
		if(l==r)val[id]=A[l];
		else{
			int m=(l+r)>>1;
			build(ls);
			build(rs);
			update(id);
		}
	}
	void modify(int l,int r,int id){
		if(l==r)val[id]+=off;
		else{
			int m=(l+r)>>1;
			if(py<=m)modify(ls);
			else modify(rs);
			update(id);
		}
	}
	void query(int l,int r,int id){
		if(nl1<=l && r<=nr1)res=gcd(res,val[id]);
		else{
			int m=(l+r)>>1;
			if(nl1<=m)query(ls);
			if(m<nr1)query(rs);
		}
	}
};
Seg1D pt,lt,rt;
void buildHelper(int l,int r,int id){
	if(l==r)pt.val[id]=gcd(lt.val[id],rt.val[id]);
	else{
		int m=(l+r)>>1;
		buildHelper(ls);
		buildHelper(rs);
		pt.update(id); 
	}
}
void modifyHelper(int l,int r,int id){
	if(l==r)pt.val[id]=gcd(lt.val[id],rt.val[id]);
	else{
		int m=(l+r)>>1;
		if(py<=m)modifyHelper(ls);
		else modifyHelper(rs);
		pt.update(id);
	}
}
void mergeBuild(Seg1D p,Seg1D l,Seg1D r){
	pt=p,lt=l,rt=r;
	buildHelper(1,M,1);
}
void mergeModify(Seg1D p,Seg1D l,Seg1D r){
	pt=p,lt=l,rt=r;
	modifyHelper(1,M,1);
}
Int64 nl2,nr2,px;
struct Seg2D{
	Seg1D root[size<<2];
	void build(int l,int r,int id){
		root[id]=Seg1D(M);
		if(l==r){
			int x=l;
			for(int y=1;y<=M;++y)
				A[y]=getVal(x,y)-getVal(x-1,y)-getVal(x,y-1)+getVal(x-1,y-1);
			root[id].build(1,M,1); 
		}
		else{
			int m=(l+r)>>1;
			build(ls);
			build(rs);
			mergeBuild(root[id],root[id<<1],root[id<<1|1]);
		}
	}
	void modify(int l,int r,int id){
		if(l==r)root[id].modify(1,M,1);
		else{
			int m=(l+r)>>1;
			if(px<=m)modify(ls);
			else modify(rs);
			mergeModify(root[id],root[id<<1],root[id<<1|1]);
		}
	}
	void query(int l,int r,int id){
		if(nl2<=l && r<=nr2)root[id].query(1,M,1);
		else{
			int m=(l+r)>>1;
			if(nl2<=m)query(ls);
			if(m<nr2)query(rs);
		}
	}
} seg2D;
void modify1D(Seg1D p,int pos,int siz,Int64 add){
	if(1<=pos && pos<=siz){
		py=pos,off=add;
		p.modify(1,siz,1);
	}
}
void modify2D(int x,int y,Int64 add){
	if(1<=x && x<=N && 1<=y && y<=M){
		px=x,py=y,off=add;
		seg2D.modify(1,N,1); 
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
	
	seg2D.build(1,N,1); 
	
	Seg1D xt(M),yt(N);
	for(int i=1;i<=M;++i)
		A[i]=getVal(x,i)-getVal(x,i-1);	
	xt.build(1,M,1); 
	for(int i=1;i<=N;++i)
		A[i]=getVal(i,y)-getVal(i-1,y);
	yt.build(1,N,1); 
	Int64 mid=getVal(x,y);
	for(int i=0;i<t;++i){
		int op=read();
		if(op){
			int bx=read();
			int by=read();
			int ex=read();
			int ey=read();
			Int64 add=read();
			bool xf=bx<=x && x<=ex;
			bool yf=by<=y && y<=ey;
			if(xf && yf)mid+=add;
			if(xf)modify1D(xt,by,M,add),modify1D(xt,ey+1,M,-add);
			if(yf)modify1D(yt,bx,N,add),modify1D(yt,ex+1,N,-add);
			modify2D(bx,by,add);
			modify2D(bx,ey+1,-add);
			modify2D(ex+1,by,-add);
			modify2D(ex+1,ey+1,add);
		}
		else{
			int bx=x-read()+1;
			int by=y-read()+1;
			int ex=x+read();
			int ey=y+read();
			res=mid;
			nl1=by,nr1=ey;
			xt.query(1,M,1);
			nl1=bx,nr1=ex;
			yt.query(1,N,1);
			nl1=by,nr1=ey;
			nl2=bx,nr2=ex;
			seg2D.query(1,N,1); 
			printf("%lld\n",res);
		}
	}
	return 0;
}

