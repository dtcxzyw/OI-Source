#include <cstdio>
long long S[100001]={};
bool check(double x,int n){
	//S[n]-S[r]+S[l-1]<=x(n+r-l+1)
	//(S[n]-xn)-(S[r]-xr)+(S[l-1]-x(l-1))<=0
	double c=S[n]-x*n,minv=S[1]-x;
	for(int i=2;i<n;++i){
		double sub=S[i]-x*i;
		if(c+minv<=sub)return true;
		if(minv>sub)minv=sub;
	}
	return false;
}
int main(){
	int n,x,maxv=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		if(x>maxv)maxv=x;
		S[i]=S[i-1]+x;
	}
	double l=0.0,r=maxv;
	while(r-l>=0.0001){
		double mid=(l+r)/2.0;
		if(check(mid,n))r=mid;
		else l=mid;
	}
	printf("%.3lf\n",l);
	return 0;
}

