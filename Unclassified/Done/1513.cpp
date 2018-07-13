#include <cstdio>
#include <cmath>
double x[100],y[100];
int main(){
	int n;
	double r;
	scanf("%d%lf",&n,&r);
	for(int i=0;i<n;++i)
		scanf("%lf%lf",&x[i],&y[i]);
	double sum=2.0*acos(-1.0)*r;
	for(int i=0;i<n;++i){
		int j=(i+1)%n;
		double dx=x[i]-x[j],dy=y[i]-y[j];
		sum+=sqrt(dx*dx+dy*dy);
	}
	printf("%.2lf\n",sum);
	return 0;
}

