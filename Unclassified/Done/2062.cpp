#include <cstdio>
#include <algorithm>
const int size=1000001;
int A[size],f1[size]={},f2[size]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&A[i]);
	std::sort(A+1,A+n+1);
	for(int i=1;i<=n;++i){
		if(i>=A[i])f1[i]=f2[i-A[i]]+1;
		f2[i]=std::max(f1[i],f2[i-1]);
	}
	printf("%d",f1[n]);
	return 0;
}

