#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
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
const int size=605;
struct Edge{
	int to,next;	
} E[size*size];
int last[size],ecnt;
void addEdge(int u,int v){
	++ecnt;
	E[ecnt].to=v,E[ecnt].next=last[u];
	last[u]=ecnt;
}
int dis[size],q[size];
bool flag[size]={};
int SPFA(int s){
	memset(dis,0x3f,sizeof(dis));
	int b=0,e=1;
	q[b]=s,dis[s]=0,flag[s]=true;
	while(b!=e){
		int u=q[b++];
		if(b==size)b=0;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				if(!flag[v]){
					flag[v]=true;
					q[e++]=v;
					if(e==size)e=0;
				}
			}
		}
	}
}
struct Vec{
	FT x,y;
	Vec(){}
	Vec(FT x,FT y):x(x),y(y){}	
	void read(){
		x=::read();
		y=::read();
	}
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
FT distance2(const Vec& a,const Vec& b){
	FT dx=a.x-b.x,dy=a.y-b.y;
	return dx*dx+dy*dy;
}
FT cross(const Vec& a,const Vec& b){
	return a.x*b.y-b.x*a.y;
}
struct Line{
	Vec ori,dir;
	FT ang;
	int id;
	bool operator<(const Line& rhs) const{
		return ang<rhs.ang;
	}
	bool onLeft(const Vec& p) const{
		return cross(dir,p-ori)>0.0;
	}
} L[size],A[4];
Vec intersect(const Line& a,const Line& b){
	Vec delta=a.ori-b.ori;
	FT t=cross(b.dir,delta)/cross(a.dir,b.dir);
	return a.ori+a.dir*t;
}
Vec P[size];
void solve(int n,int src){
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
	if(e-b+1<3)return;
	for(int i=b;i<=e;++i)
		addEdge(src,L[q[i]].id);
}
Vec S[size];
Line border(const Vec& a,const Vec& b){
	Line line;
	line.ori=a;
	line.dir=b-a;
	line.ang=atan2(line.dir.y,line.dir.x);
	line.id=0;
	return line;
}
Line calc(const Vec& a,const Vec& b,int id){
	Line line;
	line.ori=(a+b)*0.5;
	Vec delta=b-a;
	line.dir=Vec(-delta.y,delta.x);
	line.ang=atan2(line.dir.y,line.dir.x);
	line.id=id;
	return line;
}
int foo(){
	memset(last,0,sizeof(last));
	ecnt=0;
	int n=read();
	{
		Vec rt;
		rt.read();
		Vec vert[4];
		for(int i=0;i<4;++i)
			vert[i]=Vec((i+1)&2?rt.x:0.0,i&2?rt.y:0.0);
		for(int i=0;i<4;++i)
			A[i]=border(vert[i],vert[(i+1)&3]);
	}
	Vec s;
	s.read();
	for(int i=1;i<=n;++i)S[i].read();
	for(int i=1;i<=n;++i){
		int cnt=4;
		memcpy(L,A,sizeof(Line)*4);
		for(int j=1;j<=n;++j)
			if(i!=j)
				L[cnt++]=calc(S[i],S[j],j);
		solve(cnt,i);
	}
	int id=-1;
	FT mdis=1e20;
	for(int i=1;i<=n;++i){
		FT cdis=distance2(s,S[i]);
		if(cdis<mdis)
			mdis=cdis,id=i;
	}
	if(id==-1)return 0;
	else{
		SPFA(id);
		return dis[0];
	}
}
int main(){
	int t=read();
	while(t--)printf("%d\n",foo());
	return 0;
}

