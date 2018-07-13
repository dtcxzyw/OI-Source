#include <cstdio>
//f(1)=0
//f(n)=(f(n-1)*(n-2)+2*(f(n-1)+1))/n=f(n-1)+2/n;
double foo1(int n){
	double res=0.0;
	for(int i=2;i<=n;++i)res+=2.0/i;
	return res;
}
const int size=110;
double f[size][size];
int maxv(int a,int b){
	return a>b?a:b;
}
double foo2(int n){
	f[1][0]=1.0;
	for(int i=2;i<=n;++i)
		for(int l=1;l<i;++l){
			int r=i-l;
			for(int lh=0;lh<l;++lh)
				for(int rh=0;rh<r;++rh)
					f[i][maxv(lh,rh)+1]+=f[l][lh]*f[r][rh]/(i-1);//1 + i-1 2 + i-2 ... i-1 + 1
		}
	double res=0.0;
	for(int i=1;i<=n;++i)res+=i*f[n][i];
	return res;
}
int main(){
	int op,n;
	scanf("%d%d",&op,&n);
	printf("%.6lf\n",op==1?foo1(n):foo2(n));
	return 0;
}

