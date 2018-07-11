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
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
const int size=50005;
int s[size]={},p[6000],mu[size]={};
bool flag[size]={};
void pre(int n){
	int pcnt=0;
	mu[1]=1;
	for(int i=2;i<=n;++i){
		if(!flag[i]){
			p[pcnt++]=i;
			mu[i]=-1;
		}
		for(int j=0;j<pcnt && p[j]*i<=n;++j){
			int val=p[j]*i;
			flag[val]=true;
			if(i%p[j])mu[val]=-mu[i];
			else break;
		}
	}
	for(int i=1;i<=n;++i)mu[i]+=mu[i-1];
}
int main(){
	pre(50000);
	int t=read();
	for(int i=0;i<t;++i){
		int n=read();
		int m=read();
		int d=read();
		int end=std::min(n,m)/d;
		int block=sqrt(end);
		Int64 ans=0;
		for(int i=1,div=d;i<block;++i,div+=d)
			ans+=asInt64(mu[i]-mu[i-1])*(n/div)*(m/div);
		for(int i=block;i<=end;){
			int dn=n/i,dm=m/i;
			int j=std::min(n/dn,m/dm);
			ans+=asInt64(mu[j]-mu[i-1])*(dn/d)*(dm/d);
			i=j+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

