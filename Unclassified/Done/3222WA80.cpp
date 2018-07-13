#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
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
typedef double FT;
const double eps=1e-10;
struct Vec{
	FT x,y;
	Vec(){}
	Vec(FT px,FT py):x(px),y(py){}
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
		return *this*(1.0/rhs);
	}
};
Vec normalize(const Vec& a){
	return a/sqrt(a.x*a.x+a.y*a.y);
}
FT dot(const Vec& a,const Vec& b){
	return a.x*b.x+a.y*b.y;
}
FT cross(const Vec& a,const Vec& b){
	return a.x*b.y-b.x*a.y;
}
const int size=100005;
struct Line{
	Vec p,v;
	FT ang;
	Line(){}
	Line(Vec vp,Vec vv):p(vp),v(vv),ang(atan2(vv.y,vv.x)){}
	bool operator<(const Line& rhs) const{
		return ang<rhs.ang;
	}
} A[size][2],B[size*2],C[size*2];
Vec P[size*2];
FT distance(const Line& l,const Vec& p){
	return cross(p-l.p,l.v);
}
Vec sharedPoint(const Line& a,const Line& b){
	Vec p1=b.p;
	FT d1=distance(a,p1);
	Vec p2=b.p+b.v;
	FT d2=distance(a,p2);
	return (p1*d2-p2*d1)/(d2-d1);
}
bool onLeft(const Line& l,const Vec& p){
	return cross(l.v,p-l.p)>=0;
}
bool check(int n){
	int cnt=2*n;
	memcpy(B,A,sizeof(Line)*cnt);
	std::sort(B,B+cnt);
	int b=0,e=1;
	C[0]=B[0];
	for(int i=1;i<cnt;++i){
		while(b+1<e && !onLeft(B[i],P[e-2]))--e;
		while(b+1<e && !onLeft(B[i],P[b]))++b;
		if(fabs(cross(C[e-1].v,B[i].v))<eps){
			if(onLeft(C[e-1],B[i].p))
				C[e-1]=B[i];
		}
		else C[e++]=B[i];
		if(b+1<e)P[e-2]=sharedPoint(C[e-1],C[e-2]);
	}
	while(b+1<e && !onLeft(C[b],P[e-2]))--e;
	return e-b>=3;
}
//ax+by+c>=0 onLeft
Line makeLine(FT a,FT b,FT c){
	Vec p1,p2;
	if(fabs(b)>eps){
		p1=Vec(0.0,-c/b);
		p2=Vec(1.0,-(a+c)/b);
	}
	else{
		p1=Vec(-c/a,0.0);
		p2=Vec(-(b+c)/a,1.0);
	}
	Vec delta=p1-p2;
	Line test(p1,delta);
	if((c>=0.0)!=onLeft(test,Vec(0,0)))delta=delta*-1.0;
	return Line(p1,normalize(delta));
}
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		/*
		y=ax^2+bx
		y1<=ax^2+bx<=y2
		ax^2+bx-y1>=0
		-ax^2-bx+y2>=0
		*/
		FT x=read();
		FT x2=x*x;
		A[i][0]=makeLine(x2,x,-read());
		A[i][1]=makeLine(-x2,-x,read());
	}
	int l=0,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}

