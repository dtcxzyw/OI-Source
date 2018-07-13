#include <cstdio>
#include <set>
#include <climits>
#include <iterator>
std::multiset<long long> a;
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
int main(){
	a.insert(INT_MIN);
	a.insert(INT_MAX);
	int n=read();
	int t,v,lt=-1,ans=0;
	for(int i=0;i<n;++i){
		t=read();
		v=read();
		if(t==lt || a.size()<=2)
			a.insert(v),lt=t;
		else{
			typedef std::multiset<long long>::iterator iter_t;
			iter_t l=std::prev(a.lower_bound(v));
			iter_t r=a.upper_bound(v);
			long long dl=v-*l,dr=*r-v;
			ans=(ans+std::min(dl,dr))%1000000;
			if(dl<=dr)a.erase(l);
			else a.erase(r);
		}
	}
	printf("%d\n",ans);
	return 0;
}

