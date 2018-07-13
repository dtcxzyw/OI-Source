#include <cstdio>
#include <cmath>
#include <algorithm>
typedef long double FT;
const FT eps=1e-10;
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
struct Vec{
	FT x,y;
	Vec():x(0.0),y(0.0){}
	Vec(FT x,FT y):x(x),y(y){}
	Vec operator+(const Vec& rhs) const{
		return Vec(x+rhs.x,y+rhs.y);
	}
	Vec operator-(const Vec& rhs) const{
		return Vec(x-rhs.x,y-rhs.y);
	}
	Vec operator-() const{
		return Vec(-x,-y);
	}
	void read(){
		x=::read();
		y=::read();
	}
	Vec transform(const Vec& base,const Vec& ax,const Vec& ay);
};
FT dot(const Vec& a,const Vec& b){
	return a.x*b.x+a.y*b.y;
}
Vec normalize(const Vec& v){
	FT l=sqrt(v.x*v.x+v.y*v.y);
	return Vec(v.x/l,v.y/l);
}
Vec Vec::transform(const Vec& base,const Vec& ax,const Vec& ay){
	Vec delta=*this-base;
	return Vec(dot(ax,delta),dot(ay,delta));
}
const int size=10005;
struct Seg{
	Vec a,b;
	void read(){
		a.read();
		b.read();
	}
	void transform(const Vec& base,const Vec& ax,const Vec& ay){
		a=a.transform(base,ax,ay);
		b=b.transform(base,ax,ay);
	}
} S[size];
FT range[size][2],P[2*size];
int find(int siz,FT pos){
	return std::lower_bound(P,P+siz,pos)-P+1;
}
double foo(){
	int n=read();
	for(int i=0;i<n;++i)S[i].read();
	Vec a;a.read();
	Vec b;b.read();
	Vec ax=normalize(b-a);
	Vec ay(-ax.y,ax.x);
	for(int i=0;i<n;++i)
		S[i].transform(a,ax,ay);
	FT L=read();
	int pcnt=0;
	for(int i=0;i<L;++i){
		FT ay=fabs(S[i].a.y),by=fabs(S[i].b.y);
		if(ay>L && by>L){
			range[i][0]=0.0;
			range[i][1]=-1.0;
		}
		else{
			FT ax=S[i].a.x,bx=S[i].b.x;
			if(ay>L && by<=L){
				FT w=(L-by)/(ay-by);
				ax=bx+(ax-bx)*w;
			}
			else if(ay<=L && by>L){
				FT w=(L-ay)/(by-ay);
				bx=ax+(bx-ax)*w;
			}
			range[i][0]=fmin(ax,bx);
			range[i][1]=fmax(ax,bx);
			P[pcnt++]=ax;
			P[pcnt++]=bx;
		}
	}
	//!!!
	std::sort(P,P+pcnt);
	pcnt=std::unique(P,P+pcnt)-P;
	for(int i=0;i<L;++i)
		if(range[i][0]<range[i][1]){
			int b=find(pcnt,range[i][0]);
			int e=find(pcnt,range[i][1]);
			//[b,e)
			
		}
}
int main(){
	int t=read();
	while(t--)printf("%.15lf\n",foo());
	return 0;	
}

