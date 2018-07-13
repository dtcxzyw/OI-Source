#include <cstdio>
int d[151],prime[50],fac[50]={},pcnt=0;
bool test(int x){
	for(int i=1;i<=pcnt;++i)
		if(x%prime[i]==0)return false;
	return true;
}
void mul(int x,int off){
	for(int i=1;i<=pcnt;++i)
		while(x%prime[i]==0){
			fac[i]+=off;
			x/=prime[i];
		}
}
int main(){
	int n;
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&d[i]);
		if(d[i]==0 && n!=1){
			puts("0");
			return 0;
		}
		--d[i];
		sum+=d[i];
	}
	
	if(n-2!=sum){
		puts("0");
		return 0;
	}
		
	for(int i=2;i<150;++i)
		if(test(i))
			prime[++pcnt]=i;
	for(int i=n-1-sum;i<=n-2;++i)
		mul(i,1);
	for(int i=1;i<=n;++i)
		for(int j=2;j<=d[i];++j)
			mul(j,-1);
	long long res=1;
	for(int i=1;i<=pcnt;++i)
		for(int j=0;j<fac[i];++j)
			res=res*prime[i];
	printf("%lld\n",res);
	return 0;
}

