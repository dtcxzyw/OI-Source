#include <cstdio>
int main(){
	int n;
	scanf("%d",&n);
	for(int i=30;i>=0;--i)
		if(n&(1<<i)){
			printf("%d\n",i+1);
			break;
		}
	return 0;
}

