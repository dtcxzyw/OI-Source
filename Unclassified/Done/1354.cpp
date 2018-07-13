#include <cstdio>
#include <cmath>
#include <algorithm>
struct Point{
	double x,y;
	Point(){}
	Point(double a,double b):x(a),y(b){}
};
double dis(Point lhs,Point rhs){
	double dx=lhs.x-rhs.x,dy=lhs.y-rhs.y;
	return sqrt(dx*dx+dy*dy);
}
double cross(Point lhs,Point rhs){
	return lhs.x*rhs.y-rhs.x*lhs.y;
}
Point operator+(Point lhs,Point rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator-(Point lhs,Point rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
Point mid(Point lhs,Point rhs){
	return Point((lhs.x+rhs.x)*0.5,(lhs.y+rhs.y)*0.5);
}
bool check(Point t,Point b,Point p){
	return cross(t,p)<=0.0 && cross(b,p)>=0.0;
}
bool check(Point base,Point t,Point b,Point p){
	Point tp=t-base,bp=b-base,pp=p-base;
	return check(tp,bp,pp);
}
Point tmp[20];
int id[20],cnt[20];
bool cmp(int a,int b){
	return cross(tmp[a],tmp[b])>0.0;
}
struct Wall{
	Point bb,bt,tb,tt;
	int type;
	Wall(){}
	Wall(double x,double a1,double a2,double b1,double b2):type(2),bb(x,a1),bt(x,a2),tb(x,b1),tt(x,b2){}
	bool test(Point base,Point p) const{
		return check(base,bt,bb,p)||(type==2 && check(base,tt,tb,p));
	}
	bool merge(const Wall& rhs,Point p){
		if(type==2){
			tmp[0]=bb-p,tmp[1]=bt-p,tmp[2]=tb-p,tmp[3]=tt-p;
			tmp[4]=rhs.bb-p,tmp[5]=rhs.bt-p,tmp[6]=rhs.tb-p,tmp[7]=rhs.tt-p;	
		}
		else{
			tmp[0]=bb-p,tmp[1]=bt-p;
			tmp[2]=rhs.bb-p,tmp[3]=rhs.bt-p,tmp[4]=rhs.tb-p,tmp[5]=rhs.tt-p;
		}
		for(int i=0;i<20;++i)id[i]=i,cnt[i]=0;
		int siz=(type==2?8:6);
		std::sort(id,id+siz,cmp);
		int old=siz;
		for(int i=1;i<old;++i)tmp[siz++]=mid(tmp[id[i]],tmp[id[i-1]]);
		std::sort(id,id+siz,cmp);
		for(int i=0;i<siz;++i){
			Point x=tmp[id[i]];
			if(check(tmp[1],tmp[0],x))++cnt[i];
			if(check(tmp[3],tmp[2],x))++cnt[i];
			if(check(tmp[5],tmp[4],x))++cnt[i];
			if(type==2 && check(tmp[7],tmp[6],x))++cnt[i];
		}
		int b1=-1,e1=-10,b2=-1,e2,last=-10;
		for(int i=0;i<siz;++i)
			if(cnt[i]==2){
				if(last!=i-1){
					if(b1==-1)b1=i;
					else b2=i;
				}
				last=i;
			}
			else{
				if(e1==-10)e1=last;
				else e2=last;
			}
		if(e1==-10)e1=last;
		else e2=last;
		if(b1==-1)return false;
		else if(b2==-1)type=1,bb=tmp[id[b1]]+p,bt=tmp[id[e1]]+p;
		else type=2,bb=tmp[id[b1]]+p,bt=tmp[id[e1]]+p,tb=tmp[id[b2]]+p,tt=tmp[id[e2]]+p;
		return true;
	}
} A[21];
Point S(0.0,5.0),T(10.0,5.0);
double ans=1e50,dp[100];
int getID(int i,int j){
	return i<<2|j;
}
void CAS(double& a,double b){
	if(a>b)a=b;
}
void update(Point p,int i,int n,double val){
	++i;
	Wall bound(p.x,p.y-1,p.y+1,p.y,p.y);
	bound.type=1;
	for(;i<=n;++i){
		#define RELAX(pos,res) if(bound.test(p,pos)) CAS(res,val+dis(p,pos));
		RELAX(A[i].bb,dp[getID(i,0)]);
		RELAX(A[i].bt,dp[getID(i,1)]);
		RELAX(A[i].tb,dp[getID(i,2)]);
		RELAX(A[i].tt,dp[getID(i,3)]);
		if(!bound.merge(A[i],p))return;
	}
	RELAX(T,ans);
	#undef RELAX
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		double x,a1,a2,b1,b2;
		scanf("%lf%lf%lf%lf%lf",&x,&a1,&a2,&b1,&b2);
		A[i]=Wall(x,a1,a2,b1,b2);
		for(int j=0;j<4;++j)
			dp[getID(i,j)]=1e50;
	}
	update(S,0,n,0.0);
	for(int i=1;i<=n;++i){
		update(A[i].bb,i,n,dp[getID(i,0)]);
		update(A[i].bt,i,n,dp[getID(i,1)]);
		update(A[i].tb,i,n,dp[getID(i,2)]);
		update(A[i].tt,i,n,dp[getID(i,3)]);
	}
	printf("%.2lf\n",ans);
	return 0;
}

