#include <cstdio>
#include <algorithm>
#include <functional>
const int size=105;
int A[size]={},B[32]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&A[i]);
	std::sort(A,A+n,std::greater<int>());
	long long sum=0;
	for(int i=0;i<n;++i){
		int v=A[i];
		sum+=v;
		for(int j=30;j>=0;--j)
			if(A[i]&(1<<j)){
				if(B[j])A[i]^=B[j];
				else{
					B[j]=A[i];
					sum-=v;
					break;
				}
			}
	}
	printf("%lld\n",sum);
	return 0;
}

