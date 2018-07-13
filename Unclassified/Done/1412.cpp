#include <cstdio>
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
int t[100001],x[100001];
double maxv(double a,double b){
	return a>b?a:b;
}
int main(){
	int n,k,c,w;
	n=read();k=read();c=read();w=read();
	for(int i=1;i<=n;++i){
		t[i]=read();
		x[i]=read();
	}
	double ans=0.0,mk=1.0-0.01*k,mc=1.0+0.01*c;
	for(int i=n;i>0;--i)
		if(t[i]==1)ans=maxv(ans,ans*mk+x[i]);
		else ans=maxv(ans,ans*mc-x[i]);
	printf("%.2lf\n",ans*w);
	return 0;	
}

