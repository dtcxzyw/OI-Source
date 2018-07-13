#include <cstdio>
int main(){
	double n;
	scanf("%lf",&n);
	printf("%.14lf\n",n*(n+1.0)/(2.0*(2.0*n-1.0)));
	return 0;
}

