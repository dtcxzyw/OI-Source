#include <cstdio>
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	printImpl(x);
	putchar(' ');
}
long long f[1000001];
int main(){
	int n;
	scanf("%d",&n);
	f[0]=0;
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;j+=i)
			f[j]+=i;
	long long sum=0;
	for(int i=1;i<=n;++i){
		sum+=n-f[i];
		print(sum);	
	}
	return 0;
}

