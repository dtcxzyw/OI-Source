#include <cstdio>
long long h[10001];
void CAS(long long& a,long long b){
	if(a>b && b>0)a=b;
}
const long long fac[4]={2,3,5,7};
int main(){
	int n,l[4]={1,1,1,1};
	scanf("%d",&n);
	h[1]=1;
	for(int i=2;i<=n;++i){
		h[i]=1LL<<60;
		for(int k=0;k<4;++k){
			for(int j=l[k];j<i;++j)
				CAS(h[i],h[j]*fac[k]);
			while(h[l[k]]*fac[k]<=h[i])++l[k];
		}
	}
	printf("%lld\n",h[n]);
	return 0;
}

