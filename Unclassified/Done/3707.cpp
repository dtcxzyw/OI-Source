#include <cstdio>
int read(){
	int res=0,c;
	bool flag=false;
	do {
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int size=100100;
int IX[size],IY[size];
double sx[size<<2],sy[size<<2],sx2[size<<2],sxy[size<<2];
double lazyX[size<<2],lazyY[size<<2];
int lazy[size<<2];
void update(int id){
	sx[id]=(sx[id<<1]+sx[id<<1|1]);
	sy[id]=(sy[id<<1]+sy[id<<1|1]);
	sx2[id]=(sx2[id<<1]+sx2[id<<1|1]);
	sxy[id]=(sxy[id<<1]+sxy[id<<1|1]);
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	lazyX[id]=lazyY[id]=lazy[id]=0;
	if(l==r){
		sx[id]=IX[l],sy[id]=IY[l];
		sx2[id]=sx[id]*sx[id];
		sxy[id]=sx[id]*sy[id];
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
void push(int l,int r,int id);
void color1(int l,int r,int id,double s,double t){
	int siz=r-l+1;
	sx2[id]+=s*(sx[id]*2+s*siz);
	sxy[id]+=s*sy[id]+t*sx[id]+siz*s*t;
	sx[id]+=s*siz,sy[id]+=t*siz;
	if(lazy[id]!=1){
		push(l,r,id);
		lazy[id]=1;
	}
	lazyX[id]+=s,lazyY[id]+=t;
}
double calc(double x){
	return x*(x+1)*(x*2+1)/6;
}
void color2(int l,int r,int id,double s,double t){
	int siz=r-l+1;
	double sum=static_cast<double>(l+r)*siz/2;
	sx[id]=siz*s+sum;
	sy[id]=siz*t+sum;
	double sum2=calc(r)-calc(l-1);
	sxy[id]=siz*s*t+sum*(s+t)+sum2;
	sx2[id]=s*(siz*s+2*sum)+sum2;
	lazy[id]=2;
	lazyX[id]=s,lazyY[id]=t;
}
void push(int l,int r,int id){
	if(lazy[id]){
		if(l!=r){
			int m=(l+r)>>1;
			if(lazy[id]==1){
				color1(ls,lazyX[id],lazyY[id]);
				color1(rs,lazyX[id],lazyY[id]);	
			}
			else{
				color2(ls,lazyX[id],lazyY[id]);
				color2(rs,lazyX[id],lazyY[id]);	
			}
		}
		lazyX[id]=lazyY[id]=lazy[id]=0;
	}
}
int nl,nr,s,t;
#define Modify(type)\
void modify##type(int l,int r,int id){\
	if(nl<=l && r<=nr)color##type(l,r,id,s,t);\
	else{\
		push(l,r,id);\
		int m=(l+r)>>1;\
		if(nl<=m)modify##type(ls);\
		if(m<nr)modify##type(rs);\
		update(id);\
	}\
}

Modify(1)
Modify(2)
#undef Modify
#define Query(name,array) \
double query##name(int l,int r,int id){\
	if(nl<=l && r<=nr)return array[id];\
	else{\
		push(l,r,id);\
		int m=(l+r)>>1;\
		double res=0;\
		if(nl<=m)res+=query##name(ls);\
		if(m<nr)res+=query##name(rs);\
		return res;\
	}\
}

Query(X,sx)
Query(Y,sy)
Query(X2,sx2)
Query(XY,sxy)
#undef Query
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)IX[i]=read();
	for(int i=1;i<=n;++i)IY[i]=read();
	build(1,n,1);
	for(int i=0;i<m;++i){
		int op=read();
		nl=read();
		nr=read();
		if(op==1){
			int siz=nr-nl+1;
			double SXY=queryXY(1,n,1);
			double SX=queryX(1,n,1);
			double SY=queryY(1,n,1);
			double SX2=queryX2(1,n,1);
			//printf("SXY=%lf SX=%lf SY=%lf SX2=%lf\n",SXY,SX,SY,SX2);
			double a=SXY-SX*SY/siz;
			double b=SX2-SX*SX/siz;
			printf("%.10lf\n",a/b);
		}
		else{
			s=read();
			t=read();
			if(op==2)modify1(1,n,1);
			else modify2(1,n,1);
		}
	}
	return 0;
}

