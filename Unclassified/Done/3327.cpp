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
int minv(int a,int b){
	return a<b?a:b;
}
const int size=50100;
int prime[size],pcnt=0,mu[size],sum[size];
bool flag[size]={};
long long f[size];
long long calc(int x){
	long long res=0;
	int nxt;
	for(int i=1;i<=x;i=nxt+1){
		nxt=x/(x/i);
		res+=1LL*(nxt-i+1)*(x/i);
	}
	return res;
}
void pre(int n){
	mu[1]=1;
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[++pcnt]=i,mu[i]=-1;
		for(int j=1;j<=pcnt && i*prime[j]<=n;++j){
			flag[i*prime[j]]=true;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];	
			else{
				mu[i*prime[j]]=0;
				break;
			}
		}
	}
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1]+mu[i];
		f[i]=calc(i);
	}
}
long long foo(int n,int m){
	int x=minv(n,m),nxt;
	long long res=0;
	for(int i=1;i<=x;i=nxt+1){
		nxt=minv(n/(n/i),m/(m/i));
		res+=(sum[nxt]-sum[i-1])*f[n/i]*f[m/i];
	}
	return res;
}
int main(){
	pre(50000);
	int t=read();
	for(int i=0;i<t;++i)
		printf("%lld\n",foo(read(),read()));
	return 0;
}

