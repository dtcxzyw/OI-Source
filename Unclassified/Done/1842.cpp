#include <cstdio>
#include <algorithm>
const int size=50000;
int w[size],s[size],id[size];
bool cmp(int a,int b){
	return w[a]+s[a]<w[b]+s[b];
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&w[i],&s[i]),id[i]=i;
	std::sort(id,id+n,cmp);
	long long cw=0,maxv=-1LL<<60;
	for(int i=0;i<n;++i){
		int x=id[i];
		maxv=std::max(maxv,cw-s[x]);
		cw+=w[x];
	}
	printf("%lld\n",maxv);
	return 0;
}

