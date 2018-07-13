#include<cstdio>
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
int calc(int a,int b,int k){
	return b/k-(a-1)/k;
}
int maxv(int a,int b){
	return a>b?a:b;
}
long long f[50001];
void foo(){
	int a=read();
	int b=read();
	int c=read();
	int d=read();
	int k=read();
	int end=maxv(maxv(a,b),maxv(c,d))/k;
	for(int i=end;i>0;--i){
	    f[i]=1LL*calc(a,b,k*i)*calc(c,d,k*i);
	    for(int j=i*2;j<=end;j+=i)f[i]-=f[j];
	}
	printf("%lld\n",f[1]);
}
int main(){
	int n=read();
	for(int i=0;i<n;++i)foo();
	return 0;
}

