#include <cstdio>
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
const int size=1001000;
long long sum[size],c[size],dp[size],q[size];
double slope(int x,int y){
	return static_cast<double>(c[x]-c[y])/(sum[x]-sum[y]);
}
bool comp(double a,double b,bool flag){
	return flag?a<b:a>b;
}
int main(){
	int n=read();
	int A=read();
	int B=read();
	int C=read();
	for(int i=1;i<=n;++i)sum[i]=read()+sum[i-1];
	int b=0,e=1;
	q[0]=0;
	c[0]=C;
	bool flag=2*A<0;
	for(int i=1;i<=n;++i){
		while(e-b>1 && comp(2*A*sum[i],slope(q[b],q[b+1]),flag))++b;
		long long d=sum[i]-sum[q[b]];
		dp[i]=dp[q[b]]+((A*d+B)*d+C);
		c[i]=(A*sum[i]-B)*sum[i]+dp[i]+C;
		while(e-b>1 && slope(q[e-2],q[e-1])<slope(q[e-1],i))--e;
		q[e++]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}

