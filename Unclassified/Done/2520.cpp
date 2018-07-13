#include <cstdio>
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
bool check(int a,int b,int d){
	return a%d==0 && b%d==0;
}
int main(){
	int n=read();
	for(int i=0,a,b,x,y,d;i<n;++i){
		a=read();
		b=read();
		x=read();
		y=read();
		d=gcd(a,b)<<1;
		a%=d,b%=d,x%=d,y%=d;
		puts(check(x,y,d)||check(x+a,y+b,d)||check(x+b,y+a,d)||check(x+a+b,y+a+b,d)?"Y":"N");
	}
	return 0;
}

