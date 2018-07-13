#include <cstdio>
#include <cmath>
#include <algorithm>
const int size=105;
double A[size][size],B[size],ans[size];
bool solve(int n){
	for(int i=1;i<=n;++i){
		int x=i;
		for(int j=x+1;j<=n;++j)
			if(fabs(A[j][i])>fabs(A[x][i]))
				x=j;
		if(fabs(A[x][i])<=1e-8)return false;
		if(x!=i){
			for(int j=i;j<=n;++j)
				std::swap(A[i][j],A[x][j]);
			std::swap(B[i],B[x]);
		}
		for(int j=i+1;j<=n;++j){
			double mul=A[j][i]/A[i][i];
			for(int k=i;k<=n;++k)
				A[j][k]-=A[i][k]*mul;
			B[j]-=B[i]*mul;
		}
	}
	for(int i=n;i>=1;--i){
		double sum=B[i];
		for(int j=i+1;j<=n;++j)
			sum-=ans[j]*A[i][j];
		ans[i]=sum/A[i][i];
	}
	return true;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			scanf("%lf",&A[i][j]);
		scanf("%lf",&B[i]);
	}
	if(solve(n)){
		for(int i=1;i<=n;++i)
			printf("%.2lf\n",ans[i]);
	}
	else puts("No Solution");
	return 0;
}

