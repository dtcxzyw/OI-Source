#include <cstdio>
#include <algorithm>
#include <cmath>
const int size=2010;
struct RECT{
	int x1,y1,x2,y2;
} A[size];
double dis(int x1,int y1,int x2,int y2){
	double dx=x1-x2,dy=y1-y2;
	return sqrt(dx*dx+dy*dy);
}
bool checkLine(int x1,int xi1,int y1,int x2,int xi2,int y2){
	for(int x=xi1;x<xi2;++x){
		int by=std::max(A[x].y1,A[x+1].y1),ey=std::min(A[x].y2,A[x+1].y2);
		double w=static_cast<double>(A[x].x2-x1)/(x2-x1);
		double y=y1*(1.0-w)+y2*w;
		if(y<by || y>ey)return false;
	}
	return true;
}
int tx,txi,ty;
double dfs(int sx,int sxi,int sy){
	double s=0.0;
	while(!checkLine(sx,sxi,sy,tx,txi,ty)){
		for(int x=txi-1;x>=sxi;--x){
			int by=std::max(A[x].y1,A[x+1].y1),ey=std::min(A[x].y2,A[x+1].y2);
			double w=static_cast<double>(A[x].x2-sx)/(tx-sx);
			double y=sy*(1.0-w)+ty*w;
			int choose=1<<30;
			bool br=checkLine(sx,sxi,sy,A[x].x2,x+1,by);
			bool er=checkLine(sx,sxi,sy,A[x].x2,x+1,ey);
			if(br&&er){
				if(y<=by)choose=by;
				else if(y>=ey)choose=ey;
				else{
					double bs=dfs(A[x].x2,x+1,by)+dis(sx,sy,A[x].x2,by);
					double es=dfs(A[x].x2,x+1,ey)+dis(sx,sy,A[x].x2,ey);
					return s+std::min(bs,es);
				}
			}
			else if(br)choose=by;
			else if(er)choose=ey;
			if(choose!=1<<30){
				s+=dis(sx,sy,A[x].x2,choose);
				sx=A[x].x2,sxi=x+1,sy=choose;
				break;
			}
		}
	}
	s+=dis(sx,sy,tx,ty);
	return s;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
	int sx,sy;
	scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
	double v;
	scanf("%lf",&v);
	int sxi;
	for(int i=1;i<=n;++i){
		if(A[i].x1<=sx && sx<=A[i].x2)sxi=i;
		if(A[i].x1<=tx && tx<=A[i].x2)txi=i;
	}
	if(sxi>txi){
		std::swap(sx,tx);
		std::swap(sxi,txi);
		std::swap(sy,ty);
	}
	printf("%.8lf",dfs(sx,sxi,sy)/v);
	return 0;
}

