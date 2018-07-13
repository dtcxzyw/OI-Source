#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double FT;
const int size=40001;
bool equal(FT a,FT b){
	return abs(a-b)<1e-8;
}
struct Point{
	FT x,y;
	Point(){}
	Point(FT a,FT b):x(a),y(b){}
	Point operator+(const Point& rhs) const{
		return Point(x+rhs.x,y+rhs.y);
	}
	Point operator-(const Point& rhs) const{
		return Point(x-rhs.x,y-rhs.y);
	}
	FT length2() const{
		return x*x+y*y;
	}
	FT length() const{
		return sqrt(length2());
	}
	bool operator<(const Point& rhs) const{
		return equal(y,rhs.y)?x<rhs.x:y<rhs.y;
	}
	bool operator==(const Point& rhs) const{
		return equal(x,rhs.x) && equal(y,rhs.y);
	}
} P[size];
int cnt=0;
Point rotate(FT x,FT y,FT st,FT ct){
	return Point(x*ct-y*st,x*st+y*ct);
}
FT a,b,r;
void addRECT(FT x,FT y,FT theta){
	Point base(x,y);
	FT st=sin(theta),ct=cos(theta);
	P[cnt++]=base+rotate(b,a,st,ct);
	P[cnt++]=base+rotate(-b,a,st,ct);
	P[cnt++]=base+rotate(b,-a,st,ct);
	P[cnt++]=base+rotate(-b,-a,st,ct);
}
int stack[size],scnt=0;
inline Point top(){
	return P[stack[scnt]];
}
inline Point second(){
	return P[stack[scnt-1]];
}
inline void push(int x){
	stack[++scnt]=x;
}
inline void pop(){
	--scnt;
}
inline FT cross(const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-rhs.x*lhs.y;
}
bool turn(const Point& lhs,const Point& rhs,const Point& base){
	Point d1=lhs-base,d2=rhs-base;
	FT c=cross(d1,d2);
	if(equal(c,0.0))return d1.length2()<d2.length2();
	return c<0.0;
}
bool cmp1(const Point& lhs,const Point& rhs){
	return turn(rhs,lhs,P[0]);
}
bool cmp2(const Point& lhs,const Point& rhs){
	Point d1=lhs-P[0],d2=rhs-P[0];
	return equal(cross(d1,d2),0.0);
}
void GS(){
	sort(P,P+cnt);
	cnt=unique(P,P+cnt)-P;
	sort(P+1,P+cnt,cmp1);
	cnt=unique(P+1,P+cnt,cmp2)-P;
	push(0);push(1);push(2);
	for(int i=3;i<cnt;++i){
		while(turn(top(),P[i],second()))pop();
		push(i);
	}
}
int main(){
	int n;
	scanf("%d",&n);
	scanf("%lf%lf%lf",&a,&b,&r);
	a=a/2.0-r,b=b/2.0-r;
	FT x,y,theta;
	for(int i=0;i<n;++i){
		scanf("%lf%lf%lf",&x,&y,&theta);
		addRECT(x,y,theta);
	}
	GS();
	FT ans=6.28318530717958*r;
	for(int i=1;i<=scnt;++i){
		int nxt=i%scnt+1;
		ans+=(P[stack[i]]-P[stack[nxt]]).length();
	}
	printf("%.2lf\n",ans);
	return 0;
}

