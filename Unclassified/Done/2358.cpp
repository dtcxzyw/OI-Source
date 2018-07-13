#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
double length2(double x,double y){
	return x*x+y*y;
}
void CAS(double& a,double x,double y){
	double l=length2(x,y);
	a=min(a,l);
}
int main(){
	double bx,by,ex,ey;
	scanf("%lf%lf%lf%lf",&bx,&by,&ex,&ey);
	double ans=100.0;
	CAS(ans,bx-ex,(0.5-by)+(0.5-ey)+1.0);
	CAS(ans,bx-ex,(by+0.5)+(ey+0.5)+1.0);
    CAS(ans,by-ey,(0.5-bx)+(0.5-ex)+1.0);
    CAS(ans,by-ey,(bx+0.5)+(ex+0.5)+1.0);
	printf("%.3lf\n",sqrt(ans));
	return 0;
}

