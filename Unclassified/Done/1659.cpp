#include <cstdio>
#include <algorithm>
const int size=1000500,mod=19930726;
char buf[size];
int r[size]={};
long long powm(long long a,int k){
	long long res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
long long S[size]={};
int main(){
	long long n,k;
	buf[0]='#';
	scanf("%lld%lld%s",&n,&k,buf+1);
	int cur=0,right=0,maxr=0;
	for(int i=1;i<=n;++i){
		if(i<right)r[i]=std::min(r[cur*2-i],right-i);
		else r[i]=0;
		while(buf[i-r[i]-1]==buf[i+r[i]+1])++r[i];
		if(i+r[i]>right){
			cur=i;
			right=i+r[i];
		}
		++S[r[i]];
		if(r[i]>maxr)maxr=r[i];
	}
	long long res=1;
	for(int i=maxr;i>=0;--i){
		long long val=std::min(S[i],k);
		res=res*powm(1+2*i,val)%mod;
		k-=val;
		if(k==0)break;
		if(i)S[i-1]+=S[i];
	}
	if(k)puts("-1");
	else printf("%lld\n",res);
	return 0;
}

