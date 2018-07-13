#include <cstdio>
#include <set>
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
const int size=201000;
struct Circle{
	int x,y,r;
} A[size];
struct Point{
	int id,x;
	bool op;
	Point(){}
	Point(int i,int px,bool f):id(i),x(px),op(f){}
	bool operator<(Point rhs) const{
		return x<rhs.x;
	}
} B[size*2];
int cx;
double calcY(Circle c,int k){
	double dx=cx-c.x,r=c.r;
	return c.y+k*sqrt(r*r-dx*dx);
}
struct Info{
	int id,k;
	Info(int i,int f):id(i),k(f){}
	bool operator<(Info rhs) const{
		if(id==rhs.id)return k<rhs.k;
		double y1=calcY(A[id],k);
		double y2=calcY(A[rhs.id],rhs.k);
		return y1==y2?id<rhs.id:y1<y2;
	}
};
int flag[size];
int main(){
	int n=read();
	int cnt=0;
	for(int i=1;i<=n;++i){
		A[i].x=read();
		A[i].y=read();
		A[i].r=read();
		B[cnt++]=Point(i,A[i].x-A[i].r,true);
		B[cnt++]=Point(i,A[i].x+A[i].r,false);
	}
	std::sort(B,B+cnt);
	long long ans=0;
	std::set<Info> S;
	for(int i=0;i<cnt;++i){
		cx=B[i].x;
		if(B[i].op){
			std::set<Info>::iterator it=S.lower_bound(Info(B[i].id,-1));
			if(it==S.end())flag[B[i].id]=1;
			else if(it->k==1)flag[B[i].id]=-flag[it->id];
			else flag[B[i].id]=flag[it->id];
			long long r=A[B[i].id].r;
			ans+=flag[B[i].id]*r*r;
			S.insert(Info(B[i].id,-1)),S.insert(Info(B[i].id,1));
		}
		else S.erase(Info(B[i].id,-1)),S.erase(Info(B[i].id,1));
	}
	printf("%lld\n",ans);
	return 0;
}

