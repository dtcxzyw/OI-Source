#include <cstdio>
int main(){
	int n;
	scanf("%d",&n);
	n=n<<1|1;
	int cnt=0,a=1;
	do ++cnt,a=(a<<1)%n;
	while(a!=1);
	printf("%d",cnt);
	return 0;
}

