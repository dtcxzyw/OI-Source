#include <cstdio>
#include <algorithm>
const int mod=1000000007;
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
typedef std::pair<int,int> Info;
const int size=100001;
Info A[size];
int powm(int a,int k){
	int res=1;
	while(k){
		if(k&1)res=1LL*res*a%mod;
		k>>=1,a=1LL*a*a%mod;
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	int k=read();
	for(int i=0;i<k;++i){
		A[i].first=read();
		A[i].second=read();	
	}
	std::sort(A,A+k);
	int siz=std::unique(A,A+k)-A;
	int a=(1LL*n*(n+1)/2)%mod,b=0,now=1,ans=1;
	for(int i=0;i<siz;++i){
		if(i==0 || A[i].first!=A[i-1].first){
			++b;
			ans=1LL*ans*now%mod;
			now=a;
		}
		now=(now-A[i].second+mod)%mod;
	}
	ans=1LL*ans*now%mod;
	ans=1LL*ans*powm(a,m-b)%mod;
	printf("%d\n",ans);
	return 0;
}

