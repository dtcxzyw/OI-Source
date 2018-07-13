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
const double eps=1e-10,inf=1e10;
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
FT cross(const Vec& a,const Vec& b){
	return a.x*b.y-b.x*a.y;
}
bool test(const Vec& base,const Vec& a,const Vec& b){
	FT da=cross(base,a),db=cross(base,b);
	return (da<-eps && db>eps) || (da>eps && db<-eps);
}
Vec sharedPoint(const Vec& pa,const Vec& da,const Vec& pb,const Vec& db){
	Vec delta=pa-pb;
	FT t=cross(db,delta)/cross(da,db);
	return pa+da*t;
}
const int size=200005;
bool cmpLess(FT a){
	return a<eps;
}
bool cmpGreater(FT a){
	return a>-eps;
}
Vec P[size],tmp[size];
int cnt;
typedef bool(*Func)(FT);
template<Func func>
bool insert(const Vec& base,const Vec& dir){
	P[cnt]=P[0];
	int ncnt=0;
	for(int i=0;i<cnt;++i){
		Vec cur=P[i],nxt=P[i+1];
		Vec dcur=cur-base,dnxt=nxt-base;
		if(func(cross(dir,dcur)))tmp[ncnt++]=cur;
		if(test(dir,dcur,dnxt))
			tmp[ncnt++]=sharedPoint(base,dir,cur,nxt-cur);
	}
	cnt=ncnt;
	memcpy(P,tmp,sizeof(Vec)*cnt);
	return cnt;
}
int main(){
	cnt=4;
	//a<0 b>0
	P[0]=Vec(0,inf);
	P[1]=Vec(0,0);
	P[2]=Vec(-inf,0);
	P[3]=Vec(-inf,inf);
	int n=read();
	int ans=0;
	for(int i=0;i<n;++i){
		FT x=read();
		FT y1=read();
		FT y2=read();
		//y=ax^2+bx
		//y/x=ax+b
		//y1/x<=ax+b<=y2/x on right
		if(insert<cmpGreater>(Vec(0,y1/x),Vec(1,-x)) && insert<cmpLess>(Vec(0,y2/x),Vec(1,-x)))++ans;
		else break;
	}
	printf("%d\n",ans);
	return 0;
}

