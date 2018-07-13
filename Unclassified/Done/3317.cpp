#include <cstdio>
#include <cmath>
#include <algorithm>
const int size=60;
double P[size][size];
const double eps=1e-8;
double clamp(double x){
	return x>eps?x:eps;
}
double slove(int n){
	double res=1.0;
	for(int i=1;i<=n;++i){
		int base=i;
		for(int j=i+1;j<=n;++j)if(fabs(P[j][i])>fabs(P[base][i]))base=j;
		if(i!=base)for(int j=1;j<=n;++j)std::swap(P[i][j],P[base][j]);
		if(fabs(P[i][i])<eps)return 0.0;
		res*=P[i][i];
		for(int j=i+1;j<=n;++j){
			double t=-P[j][i]/P[i][i];
			for(int k=i;k<=n;++k)
				P[j][k]+=P[i][k]*t;
		}
	}
	return fabs(res);
}
int main(){
	int n;
	scanf("%d",&n);
	double k=1.0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			scanf("%lf",&P[i][j]);
			double x=clamp(1.0-P[i][j]);
			if(i<j)k*=x;
			P[i][j]/=x;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)
				P[i][i]-=P[i][j];
	printf("%.8lf\n",slove(n-1)*k);
	return 0;
}

