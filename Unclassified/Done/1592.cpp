#include <cstdio>
bool gcd(int a,int b){
	return b?gcd(b,a%b):a==1;
}
int A[1000001];
int main(){
	int n,k,cnt=0;
	scanf("%d%d",&n,&k);
	--k;
	for(int i=1;i<n;++i)
		if(gcd(i,n))
			A[cnt++]=i;
	printf("%d\n",k/cnt*n+A[k%cnt]);
	return 0;
}

