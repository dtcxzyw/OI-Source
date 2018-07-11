#include <cstdio>
#include <algorithm>
#include <cmath>
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
typedef long double FT;
const FT eps=1e-12;
const int size=305;
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
	Vec operator*(FT k) const{
		return Vec(x*k,y*k);
	}
};
FT cross(const Vec& a,const Vec& b){
	return a.x*b.y-b.x*a.y;
}
struct Line{
	Vec ori,dir;
	FT ang;
	bool operator<(const Line& rhs) const{
		return ang<rhs.ang;
	}
	bool onLeft(const Vec& p) const{
		return cross(dir,p-ori)>0.0;
	}
} L[size];
Vec intersect(const Line& a,const Line& b){
	Vec delta=a.ori-b.ori;
	FT t=cross(b.dir,delta)/cross(a.dir,b.dir);
	return a.ori+a.dir*t;
}
Vec lerp(const Vec& a,const Vec& b,FT p){
	if(fabs(b.x-a.x)<eps)return a;
	return a*((b.x-p)/(b.x-a.x))+b*((p-a.x)/(b.x-a.x));
}
Vec P[size];
int q[size],x[size],y[size];
FT solve(int n){
	std::sort(L+1,L+n+1);
	int b=0,e=0;
	q[0]=1;
	for(int i=2;i<=n;++i){
		while(b<e && !L[i].onLeft(P[e-1]))--e;
		while(b<e && !L[i].onLeft(P[b]))++b;
		if(fabs(cross(L[q[e]].dir,L[i].dir))>eps)q[++e]=i;
		else if(L[q[e]].onLeft(L[i].ori))q[e]=i;
		if(b<e)P[e-1]=intersect(L[q[e]],L[q[e-1]]);
	}
	while(b<e && !L[q[b]].onLeft(P[e-1]))--e;
	P[e]=intersect(L[q[b]],L[q[e]]);
	FT minh=1e20;
	for(int i=b;i<=e;++i){
		Vec l=P[i],r=P[i==e?b:i+1];
		if(l.x>r.x)std::swap(l,r);
		for(int j=1;j<n;++j){
			Vec cl(x[j-1],y[j-1]);
			Vec cr(x[j],y[j]);
			if(cl.x>r.x)break;
			if(cr.x<l.x)continue;
			FT lx=std::max(l.x,cl.x),rx=std::min(r.x,cr.x);
			l=lerp(l,r,lx),r=lerp(l,r,rx);
			cl=lerp(cl,cr,lx),cr=lerp(cl,cr,rx);
			minh=std::min(minh,std::min(l.y-cl.y,r.y-cr.y));
		}
	}
	return std::max(minh,0.0l);
}
int main(){
	int n=read();
	for(int i=0;i<n;++i)x[i]=read();
	for(int i=0;i<n;++i)y[i]=read();
	for(int i=1;i<n;++i){
		L[i].ori=Vec(x[i-1],y[i-1]);
		L[i].dir=Vec(x[i]-x[i-1],y[i]-y[i-1]);
		L[i].ang=atan2(L[i].dir.y,L[i].dir.x);
	}
	L[n].ori=Vec(1e20,1e20);
	L[n].dir=Vec(-1,0);
	L[n].ang=atan2(0,-1);
	printf("%.3lf\n",static_cast<double>(solve(n)));
	return 0;
}

