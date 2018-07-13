#include <cstdio>
#include <cmath>
#include <algorithm>
typedef double FT;
const FT eps=1e-8;
struct Vec{
	FT x,y,z;
	Vec(){}
	Vec(FT x,FT y,FT z):x(x),y(y),z(z){}
	Vec operator+(const Vec& rhs) const{
		return Vec(x+rhs.x,y+rhs.y,z+rhs.z);
	}
	Vec operator-(const Vec& rhs) const{
		return Vec(x-rhs.x,y-rhs.y,z-rhs.z);
	}
	Vec operator*(FT rhs) const{
		return Vec(x*rhs,y*rhs,z*rhs);
	}
};
Vec cross(const Vec& a,const Vec& b){
	return Vec(a.y*b.z-b.y*a.z,a.z*b.x-b.z*a.x,a.x*b.y-b.x*a.y);
}
FT dot(const Vec& a,const Vec& b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
FT length(const Vec& a){
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}
FT area2(const Vec& a,const Vec& b,const Vec& c){
	return length(cross(b-a,c-a));
}
FT vol6(const Vec& a,const Vec& b,const Vec& c,const Vec& d){
	Vec ab=b-a,ac=c-a,ad=d-a;
	return dot(cross(ab,ac),ad); 
}
const int size=2005;
Vec P[size];
struct Face{
	int a,b,c;
	Face(){}
	Face(int a,int b,int c):a(a),b(b),c(c){}
	FT area2() const{
		return ::area2(P[a],P[b],P[c]);
	}
	FT vol6(int id) const{
		return ::vol6(P[a],P[b],P[c],P[id]);
	}
};
Face face[6*size];
int fcnt=0,pre[6*size]={},nxt[6*size]={},fid[size][size]={},tail=0;
void add(const Face& f){
	int id=++fcnt;
	fid[f.a][f.b]=fid[f.b][f.c]=fid[f.c][f.a]=id;
	nxt[tail]=id;
	pre[id]=tail;
	tail=id;
	face[id]=f;
}
void erase(int id){
	Face f=face[id];
	fid[f.a][f.b]=fid[f.b][f.c]=fid[f.c][f.a]=0;
	if(id==tail)tail=pre[id];
	int p=pre[id],n=nxt[id];
	nxt[p]=n,pre[n]=p;
}
void erase(int i,int fi);
void testEdge(int i,int a,int b){
	int id=fid[a][b];
	if(id){
		if(face[id].vol6(i)>eps)erase(i,id);
		else add(Face(b,a,i));
	}
}
void erase(int i,int fi){
	erase(fi);
	testEdge(i,face[fi].b,face[fi].a);
	testEdge(i,face[fi].c,face[fi].b);
	testEdge(i,face[fi].a,face[fi].c);
}
FT foo(){
	int n;
	scanf("%d",&n);
	if(n<4)return 0.0;
	for(int i=0;i<n;++i)
		scanf("%lf%lf%lf",&P[i].x,&P[i].y,&P[i].z);
	
	int flag=0;
	for(int i=2;i<n;++i)
		if(fabs(area2(P[0],P[1],P[i]))>eps){
			std::swap(P[2],P[i]);
			++flag;
			break;
		}
	if(flag!=1)return 0.0;
	for(int i=3;i<n;++i)
		if(fabs(vol6(P[0],P[1],P[2],P[i]))>eps){
			std::swap(P[3],P[i]);
			++flag;
			break;
		}
	if(flag!=2)return 0.0;

	P[n]=(P[0]+P[1]+P[2]+P[3])*0.25;
	for(int i=0;i<4;++i){
		Face f(i,(i+1)&3,(i+2)&3);
		if(f.vol6(n)>0.0)std::swap(f.a,f.c);
		add(f);
	}
	
	for(int i=4;i<n;++i){
		for(int j=nxt[0];j;j=nxt[j])
			if(face[j].vol6(i)>eps){
				erase(i,j);
				break;
			}
	}
	FT res=0.0;
	for(int i=nxt[0];i;i=nxt[i])
		res+=face[i].area2();
	return 0.5*res;
}
int main(){
	printf("%.3lf\n",foo());
	return 0;
}

