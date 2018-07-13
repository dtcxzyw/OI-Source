#include <cstdio>
#include <map>
typedef long long intt;
int main(){
	intt n,k;
	scanf("%lld%lld",&n,&k);
	std::map<intt,int> fac;
	for(intt i=2;k!=1;++i)
		if(k%i==0){
			while(k%i==0){
				++fac[i];
				k/=i;
			}
		}
	typedef std::map<intt,int>::iterator iter_t;
	intt ans=1LL<<60;
	for(iter_t i=fac.begin();i!=fac.end();++i){
		intt x=0;
		for(intt j=i->first;j<=n;j*=i->first)x+=n/j;
		x/=i->second;
		if(x<ans)ans=x;
	}
	printf("%lld\n",ans);	
	return 0;
}

