#include <cstdio>
#include <cmath>
struct Point{
	double x,y;
	Point(){}
	Point(int a,int b):x(a),y(b){}
	Point operator-(Point rhs) const{
		return Point(x-rhs.x,y-rhs.y);
	}
	double cross(Point rhs) const {
		return x*rhs.y-rhs.x*y;
	}
	double dis(Point rhs) const{
		double dx=x-rhs.x,dy=y-rhs.y;
		return sqrt(dx*dx+dy*dy);
	}
} S,T;
bool check(Point base,Point t,Point b,Point p){
	Point dt=t-base,db=b-base,dp=p-base;
	return dt.cross(dp)<=0.0 && db.cross(dp)>=0.0;
}
int getID(int i,int j){
	return i<<2|j;
}
const int size=2010;
double ans=1e50,dp[size*4];
struct RECT{
	Point lt,lb,rt,rb;
	RECT(){}
	RECT(int bx,int by,int ex,int ey):lt(bx,ey),lb(bx,by),rt(ex,ey),rb(ex,by){}
	bool check(Point rhs) const{
		return lb.x<=rhs.x && rhs.x<=rt.x && lb.y<=rhs.y && rhs.y<=rt.y;
	}
} A[size];
void CAS(double& a,double b){
	if(a>b)a=b;
}
double maxv(double a,double b){
	return a>b?a:b;
}
double minv(double a,double b){
	return a<b?a:b;
}
void update(Point p,int i,int n,double val){
	Point t=Point(p.x,p.y+1),b=Point(p.x,p.y-1);
	for(;i<=n;++i){
		#define RELAX(P,V) if(check(p,t,b,P))CAS(V,val+p.dis(P))
		RELAX(A[i].lt,dp[getID(i,0)]);
		RELAX(A[i].lb,dp[getID(i,1)]);
		RELAX(A[i].rt,dp[getID(i,2)]);
		RELAX(A[i].rb,dp[getID(i,3)]);
		#undef RELAX
		if(A[i].check(T) && check(p,t,b,T))
			CAS(ans,val+p.dis(T));
		if(i<n){
			double x=A[i].rt.x;
			Point nt(x,minv(A[i].rt.y,A[i+1].lt.y));
			Point nb(x,maxv(A[i].rb.y,A[i+1].lb.y));
			if(p.x==x){
				if(nb.y>p.y || nt.y<p.y){
					CAS(dp[getID(i+1,0)],val+p.dis(A[i+1].lt));
					CAS(dp[getID(i+1,1)],val+p.dis(A[i+1].lb));
					return;
				}
			}
			else{
				if((t-p).cross(nt-p)<0.0)t=nt;
				if((b-p).cross(nb-p)>0.0)b=nb;
				if((t-p).cross(b-p)>0.0)return;
			}
		}
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int bx,by,ex,ey;
		scanf("%d %d %d %d",&bx,&by,&ex,&ey);
		A[i]=RECT(bx,by,ex,ey);
		for(int j=0;j<4;++j)
			dp[getID(i,j)]=1e50;
	}
	int sx,sy,tx,ty;
	scanf("%d %d %d %d",&sx,&sy,&tx,&ty);
	S=Point(sx,sy),T=Point(tx,ty);
	if(S.x>T.x){
		Point tmp=S;
		S=T;
		T=tmp;
	}
	bool state=false;
	for(int i=1;i<=n;++i){
		if(!state){
			if(state=A[i].check(S))
				update(S,i,n,0.0);
		}
		if(state){
			update(A[i].lt,i,n,dp[getID(i,0)]);
			update(A[i].lb,i,n,dp[getID(i,1)]);
			update(A[i].rt,i,n,dp[getID(i,2)]);
			update(A[i].rb,i,n,dp[getID(i,3)]);
			if(A[i].check(T))break;
		}
	}
	double v;
	scanf("%lf",&v);
	printf("%.8lf\n",ans/v);
	return 0;
}

