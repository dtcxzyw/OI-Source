#include <cstdio>
#include <algorithm>
#include <cmath>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=512;
double A[size][size]={},B[size]={},E[size]={},P[size*size];
void solve(int n){
	for(int i=1;i<n;++i){
		int x=i;
		for(int j=i+1;j<=n;++j)
			if(fabs(A[j][i])>fabs(A[x][i]))
				x=j;
		if(x!=i)for(int j=1;j<=n;++j)std::swap(A[i][j],A[x][j]);
		std::swap(B[i],B[x]);
		for(int j=i+1;j<=n;++j)
			if(fabs(A[j][i])>=1e-10){
				double t=A[j][i]/A[i][i];
				for(int k=1;k<=n;++k)
					A[j][k]-=A[i][k]*t;
				B[j]-=B[i]*t;
			}
	}
	for(int i=n;i>=1;--i){
		E[i]=B[i]/A[i][i];
		for(int j=1;j<i;++j)
			B[j]-=A[j][i]*E[i];
	}
}
bool link[size][size]={};
int deg[size]={};
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		link[u][v]=link[v][u]=true;
		++deg[u],++deg[v];
	}
	B[1]=-1.0;
	for(int i=1;i<=n;++i){
		if(i!=n){
			double p=1.0/deg[i];
			for(int j=1;j<=n;++j)
				if(link[i][j])
					A[j][i]=p;
		}
		A[i][i]-=1.0;
	}
	solve(n);
	E[n]=0.0;
	int cp=0;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(link[i][j])
				P[cp++]=E[i]/deg[i]+E[j]/deg[j];
	std::sort(P,P+m);
	double res=0.0;
	for(int i=0;i<m;++i)
		res+=(m-i)*P[i];
	printf("%.3lf\n",res);
	return 0;
}

