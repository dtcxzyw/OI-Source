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
    Vec operator-() const{
        return Vec(-x,-y);
    }
};
FT cross(const Vec& a,const Vec& b){
    return a.x*b.y-b.x*a.y;
}
const int size=200005;
struct Line{
    Vec p,d;
    FT ang;
    Line(){}
    Line(const Vec& vp,const Vec& vd):p(vp),d(vd),ang(atan2(vd.y,vd.x)){}
    bool operator<(const Line& rhs) const{
        return ang<rhs.ang;
    }
} L[size],C[size];
Vec sharedPoint(const Line& a,const Line& b){
    Vec delta=a.p-b.p;
    FT t=cross(b.d,delta)/cross(a.d,b.d);
    return a.p+a.d*t;
}
bool onLeft(const Line& l,const Vec& p){
    return cross(l.d,p-l.p)>-eps;
}
Vec S[size];
FT calcArea(Vec* A,int siz){
    FT S=0.0;
    for(int i=2;i<siz;++i)
        S+=cross(A[i-1]-A[0],A[i]-A[0]);
    return S;
}
FT solve(int n){
    std::sort(L,L+n);
    int b=0,e=1;
    C[0]=L[0];
    for(int i=1;i<n;++i){
        while(b+2<=e && !onLeft(L[i],S[e-2]))--e;
        while(b+2<=e && !onLeft(L[i],S[b]))++b;
        if(fabs(cross(C[e-1].d,L[i].d))<eps){
            if(onLeft(C[e-1],L[i].p))
                C[e-1]=L[i];
        }
        else C[e++]=L[i];
        if(b+2<=e)S[e-2]=sharedPoint(C[e-1],C[e-2]);
    }
    while(b+2<=e && !onLeft(C[b],S[e-2]))--e;
    if(e-b<3)return 0.0;
    S[e-1]=sharedPoint(C[b],C[e-1]);
    return calcArea(S+b,e-b);
}
//ax+by+c>=0 on left
struct LineDesc{
    FT a,b,c;
    LineDesc(){}
    LineDesc(FT va,FT vb,FT vc):a(va),b(vb),c(vc){}
    LineDesc operator-(const LineDesc& rhs) const{
        return LineDesc(a-rhs.a,b-rhs.b,c-rhs.c);
    }
} LD[size];
Vec P[size];
int main(){
    int n=read();
    for(int i=0;i<n;++i){
        P[i].x=read();
        P[i].y=read();
    }
    FT S1=calcArea(P,n);
    P[n]=P[0];
    for(int i=0;i<n;++i){
        /*
        S=cross(P[i]-p,P[i+1]-p)	
        =(P[i].x-p.x)*(P[i+1].y-p.y)-(P[i+1].x-p.x)*(P[i].y-p.y)
        =(P[i].y-P[i+1].y)*p.x+(P[i+1].x-P[i].x)*p.y+cross(P[i],P[i+1])
        */
        LD[i]=LineDesc(P[i].y-P[i+1].y,P[i+1].x-P[i].x,cross(P[i],P[i+1]));
    }
    int cnt=0;
    for(int i=0;i<n;++i)
        L[cnt++]=Line(P[i],P[i+1]-P[i]);
    for(int i=1;i<n;++i){
        LineDesc f=LD[i]-LD[0];
        Vec p,d;
        if(fabs(f.b)>eps)p=Vec(0.0,-f.c/f.b);
        else if(fabs(f.a)>eps) p=Vec(-f.c/f.a,0.0);
        else continue;
        d=Vec(f.b,-f.a);
        Vec tp(3243.0,213.0);
        if((f.a*tp.x+f.b*tp.y+f.c>=0) != (cross(d,tp-p)>eps))d=-d;
        L[cnt++]=Line(p,d);
    }
    FT S2=solve(cnt);
    printf("%.4lf\n",S2/S1);
    return 0;
}

