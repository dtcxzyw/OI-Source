#include <cstdio>
double a,b,c,d;
double f(double x){
	return ((a*x+b)*x+c)*x+d;
}
double calc(double l,double r){
	while(r-l>1e-3){
		double mid=(l+r)/2.0;
		if(f(mid)*f(l)<=0.0)r=mid;
		else l=mid;
	}
	return l;
}
int main(){
	scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
	for(double i=-100.1124;i<100.0;++i)
		if(f(i)*f(i+1)<0.0)
			printf("%.2lf ",calc(i,i+1));
	return 0;
}

