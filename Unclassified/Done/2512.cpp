#include <cstdio>
#include <algorithm>
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
const int size=1000001;
int A[size];
long long B[size];
long long iabs(long long x){
	return x>0?x:-x;
}
int main(){
	int n=read();
	long long sum=0;
	for(int i=0;i<n;++i){
		A[i]=read();
		sum+=A[i];
	}
	sum/=n;
	long long x=0;
	for(int i=0;i<n;++i,x-=sum){
		B[i]=x;
		x+=A[i];
	}
	std::nth_element(B,B+n/2,B+n);
	long long ans=0;
	for(int i=0;i<n;++i)
		ans+=iabs(B[i]-B[n/2]);
	printf("%lld\n",ans);
	return 0;
}

