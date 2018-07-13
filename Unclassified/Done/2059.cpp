#include <cstdio>
int A[60];
double f[60][60]={};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
		scanf("%d",&A[i]);
	f[1][1]=1.0;
	for(int i=2;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=m;++k){
				int x=A[k]%i;
				if(x==0)x=i;
				if(j<x)f[i][j]+=f[i-1][i+j-x]/m;
				else if(j>x)f[i][j]+=f[i-1][j-x]/m;
			}
		}
	}
	for(int i=1;i<=n;++i)
		printf("%.2lf%% ",f[n][i]*100.0);
	return 0;
}

