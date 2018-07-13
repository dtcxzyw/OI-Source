#include <cstdio>
#include <algorithm>
int A[100001]={};
int main(){
	int n,c,len=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&c);
		if(c>A[len])
			A[++len]=c;
		else {
			int x=std::lower_bound(A,A+len,c)-A;
			A[x]=std::min(A[x],c);
		}
	}
	printf("%d\n",n-len);
	return 0;
}

