#include <cstdio>
#include <cmath>
typedef double FT;
const int size=507;
const FT eps=1e-8;
struct Circle{
	FT p,r,r2;
	FT calc(FT x) const{
		FT dx=fabs(x-p);
		return sqrt(fmax(r2-dx*dx,0.0));
	}
} C[size];
struct Line{
	FT x1,y1,x2,y2,mul;
	Line(){}
	Line(const Circle& a,const Circle& b){
		FT dr=a.r-b.r;
		FT dis=fmin(a.r,b.r);
		FT dx=b.p-a.p;
		FT c2=dx*dx-dr*dr;
		if(c2<=0.0){
			x1=a.p,x2=b.p,y1=0.0,y2=0.0;
		}
		else{
			FT c=sqrt(c2);
			FT sa=a.r/dx,sb=b.r/dx;
			x1=a.p+dr*sa,y1=c*sa;
			x2=b.p+dr*sb,y2=c*sb;
			mul=1.0/(x2-x1);
		}
	}
	FT calc(FT x) const{
		if(x<x1 || x>x2)return 0.0;
		FT u=(x2-x)*mul,v=1.0-u;
		return u*y1+v*y2;
	}
} L[size];
int n;
FT calc(FT x){
	FT y=0.0;
	for(int i=0;i<n;++i)
		y=fmax(y,fmax(C[i].calc(x),L[i].calc(x)));
	return y;
}
FT simpson(FT l,FT r,FT fl,FT fm,FT fr){
	return (r-l)*(fl+4.0*fm+fr)/6.0;
}
FT simpsonSA(FT l,FT m,FT r,FT base,FT fl,FT fm,FT fr){
	FT lm=(l+m)*0.5,rm=(m+r)*0.5;
	FT flm=calc(lm),frm=calc(rm);
	FT sl=simpson(l,m,fl,flm,fm),sr=simpson(m,r,fm,frm,fr);
	if(fabs(sl+sr-base)<=eps)return base;
	return simpsonSA(l,lm,m,sl,fl,flm,fm)+simpsonSA(m,rm,r,sr,fm,frm,fr);
}
int main(){
	FT alpha;
	scanf("%d%lf",&n,&alpha);
	FT mul=1.0/tan(alpha),ch=0.0;
	for(int i=0;i<=n;++i){
		FT h;
		scanf("%lf",&h);
		ch+=h;
		C[i].p=ch*mul;
	}
	FT l=1e10,r=0.0;
	for(int i=0;i<=n;++i){
		if(i==n)C[i].r=1e-10;
		else scanf("%lf",&C[i].r);
		C[i].r2=C[i].r*C[i].r;
		l=fmin(l,C[i].p-C[i].r);
		r=fmax(r,C[i].p+C[i].r);
	}
	
	for(int i=0;i<n;++i)
		L[i]=Line(C[i],C[i+1]);
	
	FT m=(l+r)*0.5;
	FT fl=calc(l),fm=calc(m),fr=calc(r);
	printf("%.2lf\n",simpsonSA(l,m,r,simpson(l,r,fl,fm,fr),fl,fm,fr)*2.0);
	return 0;
}

