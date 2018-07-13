#include <cstdio>
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int k=1;k<=n;++k){
		int cnt=0;
		for(int i=1;i<=k;++i)
			for(int j=1;j<=k;++j)
				if(gcd(i,j)==1)++cnt;
		printf("%d %d\n",k,cnt);
	}
	return 0;
}

