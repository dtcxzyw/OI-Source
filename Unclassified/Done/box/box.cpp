#include <cstdio>
using FT=double;
struct Circle final{
	FT x,y,r;
	bool test(FT px,FT py) const{
		float dx=px-x,dy=py-y;
		return dx*dx+dy*dy<r;
	}
};
struct Box final{
	FT x1,y1,x2,y2;
	bool test(FT px,FT py) const{
		return x1<px && px<x2 && y1<py && py<y2;
	}
};
Circle c[501];
Box b[501];
template<typename T>
inline void swap(T& a,T& b){
	T c=a;
	a=b;
	b=c;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int ccnt=0,bcnt=0;
	char t[2];
	for(int i=0;i<n;++i){
		scanf("%s",t);
		if(*t=='c'){
			scanf("%lf%lf%lf",&c[ccnt].x,&c[ccnt].y,&c[ccnt].r);
			c[ccnt].r*=c[ccnt].r;	
			++ccnt;
		}
		else{
			scanf("%lf%lf%lf%lf",&b[bcnt].x1,&b[bcnt].y1,&b[bcnt].x2,&b[bcnt].y2);
			if(b[bcnt].x1>b[bcnt].x2)swap(b[bcnt].x1,b[bcnt].x2);
			if(b[bcnt].y1>b[bcnt].y2)swap(b[bcnt].y1,b[bcnt].y2);
			++bcnt;
		}
	}
	FT x,y;
	int ans,i,j;
	for(i=0;i<m;++i){
		scanf("%lf%lf",&x,&y);
		ans=0;
		for(j=0;j<ccnt;++j)
			ans+=c[j].test(x,y);
		for(j=0;j<bcnt;++j)
			ans+=b[j].test(x,y);
		printf("%d\n",ans);
	}
	return 0;	
}

