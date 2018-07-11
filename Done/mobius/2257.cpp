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
const int size=10000005;
int s[size]={},p[670000],mu[size]={};
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
	for(int i=0;i<pcnt;++i)
		for(int j=1;j*p[i]<=n;++j)
			s[j*p[i]]+=mu[j];
	for(int i=1;i<=n;++i)
		s[i]+=s[i-1];
}
struct Query{
	int n,m;
} Q[10005];
int main(){
	int t=read(),siz=0;
	for(int i=0;i<t;++i){
		Q[i].n=read();
		Q[i].m=read();
		siz=std::max(siz,std::max(Q[i].n,Q[i].m));	
	}
	pre(siz);
	for(int i=0;i<t;++i){
		int n=Q[i].n,m=Q[i].m;
		int end=std::min(n,m);
		int block=sqrt(end);
		Int64 ans=0;
		for(int i=1;i<block;++i)
			ans+=asInt64(s[i]-s[i-1])*(n/i)*(m/i);
		for(int i=block;i<=end;){
			int dn=n/i,dm=m/i;
			int j=std::min(n/dn,m/dm);
			ans+=asInt64(s[j]-s[i-1])*dn*dm;
			i=j+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

