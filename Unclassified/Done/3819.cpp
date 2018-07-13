#include <cstdio>
#include <algorithm>
struct Unit{
	long long p,num;
	bool operator<(const Unit& rhs) const{
		return p<rhs.p;
	}
} A[100000];
long long ABS(long long x){
	return x>0?x:-x;
}
long long test(long long pos,int n){
	long long ans=0;
	for(int i=0;i<n;++i)
		ans+=1LL*ABS(A[i].p-pos)*A[i].num;
	return ans;
}
int main(){
	long long l,n,sum=0;
	scanf("%lld%lld",&l,&n);
	for(int i=0;i<n;++i){
		scanf("%lld%lld",&A[i].p,&A[i].num);
		sum+=A[i].num;
	}
	std::sort(A,A+n);
	long long num=0,mid=sum>>1,ans;
	for(int i=0;i<n;++i){
		num+=A[i].num;
		if(num>=mid){
			ans=test(A[i].p,n);
			if(i)ans=std::min(ans,test(A[i-1].p,n));
			if(i<n-1)ans=std::min(ans,test(A[i+1].p,n));
			break;
		}
	}
	
	printf("%lld\n",ans);
	return 0;
}

