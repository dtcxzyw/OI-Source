#include <cstdio>
#include <cmath>
const double eps=1e-8;
int ax,ay,bx,by;
int cx,cy,dx,dy;
int p,q,r;
double mix(int x,int y,double k){
	return (1.0-k)*x+y*k;
}
double dis(double x1,double y1,double x2,double y2){
	double dx=x1-x2,dy=y1-y2;
	return sqrt(dx*dx+dy*dy);
}
double calc(double x1,double y1,double x2,double y2){
	return dis(ax,ay,x1,y1)/p+dis(dx,dy,x2,y2)/q+dis(x1,y1,x2,y2)/r;
}
double calc(double x1,double y1){
	double lt=0.0,rt=1.0;
	while(rt-lt>=eps){
		double lm=(2.0*lt+rt)/3.0,rm=(lt+rt*2.0)/3.0;
		double lv=calc(x1,y1,mix(cx,dx,lm),mix(cy,dy,lm))
			,rv=calc(x1,y1,mix(cx,dx,rm),mix(cy,dy,rm));
		if(lv<rv)rt=rm;
		else lt=lm;
	}
	double x2=mix(cx,dx,lt),y2=mix(cy,dy,lt);
	return calc(x1,y1,x2,y2);
}
int main(){
	scanf("%d%d%d%d",&ax,&ay,&bx,&by);
	scanf("%d%d%d%d",&cx,&cy,&dx,&dy);
	scanf("%d%d%d",&p,&q,&r);
	double lt=0.0,rt=1.0;
	while(rt-lt>=eps){
		double lm=(2.0*lt+rt)/3.0,rm=(lt+rt*2.0)/3.0;
		double lv=calc(mix(ax,bx,lm),mix(ay,by,lm))
			,rv=calc(mix(ax,bx,rm),mix(ay,by,rm));
		if(lv<rv)rt=rm;
		else lt=lm;
	}
	printf("%.2lf\n",calc(mix(ax,bx,lt),mix(ay,by,lt)));
	return 0;
}

