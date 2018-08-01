#include <cstdio>
#include <algorithm>
#include <cmath>
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
const FT eps=1e-12;
const int size=10005;
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
	return a.x*b.y-a.y*b.x;
}
struct Line{
	Vec ori,dir;
	int id;
	bool operator<(const Line& rhs) const{
		return dir.y<rhs.dir.y;
	}
	FT onLeft(const Vec& p) const{
		return cross(dir,p-ori);
	}
} L[size];
Vec intersect(const Line& a,const Line& b){
	Vec delta=a.ori-b.ori;
	FT t=cross(b.dir,delta)/cross(a.dir,b.dir);
	return a.ori+a.dir*t;
}
Vec P[size];
int q[size];
void solve(int n){
	std::sort(L,L+n+1);
	q[0]=0;
	int b=0,e=0;
	for(int i=1;i<=n;++i){
		while(b<e && L[i].onLeft(P[e-1])<-eps)--e;
		while(b<e && L[i].onLeft(P[b])<-eps)++b;
		if(fabs(cross(L[i].dir,L[q[e]].dir))>eps)q[++e]=i;
		else if(L[q[e]].onLeft(L[i].ori)>eps)q[e]=i;
		if(b<e)P[e-1]=intersect(L[q[e]],L[q[e-1]]);
	}
	while(b<e && L[b].onLeft(P[e-1])<-eps)--e;
	for(int i=b;i<=e;++i)
		q[i]=L[q[i]].id;
	std::sort(q+b,q+e+1);
	if(q[b]==0)++b;
	printf("%d\n",e-b+1);
	for(int i=b;i<=e;++i){
		printf("%d",q[i]);
		if(i<e)putchar(' ');
	}
}
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		L[i].ori=Vec(0.0,read());
		L[i].id=i+1;
	}
	for(int i=0;i<n;++i)
		L[i].dir=Vec(1.0,read());
	L[n].ori=Vec(-eps,-eps);
	L[n].dir=Vec(0.0,-1.0);
	L[n].id=0;
	solve(n);
	return 0;
}

