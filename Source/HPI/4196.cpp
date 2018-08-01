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
typedef double FT;
const FT eps=1e-12;
const int size=505;
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
Vec P[size];
int q[size];
FT solve(int n){
	std::sort(L,L+n);
	int b=0,e=0;
	q[0]=0;
	for(int i=1;i<n;++i){
		while(b<e && !L[i].onLeft(P[e-1]))--e;
		while(b<e && !L[i].onLeft(P[b]))++b;
		if(fabs(cross(L[q[e]].dir,L[i].dir))>eps)q[++e]=i;
		else if(L[q[e]].onLeft(L[i].ori))q[e]=i;
		if(b<e)P[e-1]=intersect(L[q[e]],L[q[e-1]]);
	}
	while(b<e && !L[q[b]].onLeft(P[e-1]))--e;
	P[e]=intersect(L[q[b]],L[q[e]]);
	FT area=0.0;
	for(int i=b+1;i<=e;++i)
		P[i]=P[i]-P[b];
	for(int i=b+1;i<e;++i)
		area+=cross(P[i],P[i+1]);
	return 0.5*area;
}
int main(){
	int n=read();
	int cnt=0;
	for(int i=0;i<n;++i){
		int k=read();
		for(int j=0;j<k;++j){
			int x=read();
			int y=read();
			P[j]=Vec(x,y);
		}
		for(int a=0;a<k;++a){
			int b=(a+1<k?a+1:0);
			L[cnt].ori=P[a];
			Vec dir=P[b]-P[a];
			L[cnt].dir=dir;
			L[cnt].ang=atan2(dir.y,dir.x);
			++cnt;
		}
	}
	printf("%.3lf\n",static_cast<double>(solve(cnt)));
	return 0;
}

