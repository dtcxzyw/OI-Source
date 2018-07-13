#include <cstdio>
#include <cmath>
typedef double FT;
const double eps=1e-10,inf=1e20;
int read(){
	int res;
	scanf("%d",&res);
	return res;
}
struct Vec{
	FT x,y;
	Vec(){}
	Vec(FT x,FT y):x(x),y(y){}
	Vec operator+(const Vec& rhs) const{
		return Vec(x+rhs.x,y+rhs.y);
	}
	Vec operator-(const Vec& rhs) const{
		return Vec(x-rhs.x,y-rhs.y);
	}
	Vec operator*(FT rhs) const{
		return Vec(x*rhs,y*rhs);
	}
	Vec operator/(FT rhs) const{
		return (*this)*(1.0/rhs);
	}
	Vec operator-() const{
		return Vec(-x,-y);
	}
	Vec rotate(FT theta) const{
		FT ct=cos(theta),st=sin(theta);
		return Vec(x*ct-y*st,x*st+y*ct);
	}
	FT length() const{
		return sqrt(x*x+y*y);
	}
};
FT dot(const Vec& a,const Vec& b){
	return a.x*b.x+a.y*b.y;
}
FT cross(const Vec& a,const Vec& b){
	return a.x*b.y-b.x*a.y;
}
FT sinTheta(const Vec& a,const Vec& b){
	return cross(a,b)/(a.length()*b.length());
}
struct Ray{
	Vec o,d;
	void input(){
		o.x=read();
		o.y=read();
		d.x=read();
		d.y=read();
	}
};
bool equal(FT a,FT b){
	return fabs(a-b)<=eps;
}
struct Mirror{
	Vec a,b;
	FT lambda;
	void input(){
		a.x=read();
		a.y=read();
		b.x=read();
		b.y=read();
		FT c=read();
		FT d=read();
		lambda=1.0+c/d;
	}
	bool test(const Ray& src,Ray& res,FT& mint) const{
		FT lk=src.d.x*(a.y-b.y),lb=src.d.x*(b.y-src.o.y);
		FT rk=src.d.y*(a.x-b.x),rb=src.d.y*(b.x-src.o.x);
		if(equal(lk,rk))return false;
		FT u=(rb-lb)/(lk-rk),v=1.0-u;
		if(u<-eps || v<-eps)return false;
		Vec dst=a*u+b*v;
		FT t;
		if(equal(src.d.y,0.0))t=(dst.x-src.o.x)/src.d.x;
		else t=(dst.y-src.o.y)/src.d.y;
		if(t<eps || t>=mint)return false;
		mint=t;
		Vec dir=src.o-dst,ld=a-b;
		Vec normal=Vec(-ld.y,ld.x);
		if(dot(normal,dir)<-0.0)normal=-normal;
		FT theta=asin(sinTheta(normal,dir))*lambda;
		Vec d=dir.rotate(-theta);
		res.d=d;
		res.o=dst+d*eps;
		return true;
	}
} M[105];
int main(){
	Ray ray;
	ray.input();
	int n=read(),cnt=0;
	for(int i=1;i<=n;++i)M[i].input();
	for(int i=1;i<=10;++i){
		FT t=inf;
		int id=0;
		Ray cur;
		for(int j=1;j<=n;++j){
			if(M[j].test(ray,cur,t))
				id=j;
		}
		if(id){
			printf("%d ",id);
			//printf("%lf %lf %lf %lf\n",cur.o.x,cur.o.y,cur.d.x,cur.d.y);
			ray=cur;
			++cnt;
		}
		else break;
	}
	if(cnt)puts("");
	else puts("NONE");
	return 0;
}

