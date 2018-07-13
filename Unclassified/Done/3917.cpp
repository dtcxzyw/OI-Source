#include <cstdio>
const int size=100001;
long long A[size];
bool B[size];
long long foo(int bit,int n){
	B[0]=false;
	for(int i=1;i<=n;++i)
		B[i]=B[i-1]^static_cast<bool>(A[i]&(1LL<<bit));
	long long cnt1=0,res=0;
	for(int i=1;i<=n;++i){
		if(B[i]){
			res+=i-cnt1;
			++cnt1;
		}
		else res+=cnt1;
	}
	return res;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&A[i]);
	long long ans=0;
	for(int i=0;i<64;++i)
		ans+=foo(i,n)<<i;
	printf("%lld\n",ans);
	return 0;
}

