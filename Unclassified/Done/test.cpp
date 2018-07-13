#include <cstdio>
int foo(int n,int min,int max){
	if(n==0)return 1;
	int tot=0;
	for(int i=min;i<=max;++i)
		tot+=foo(n-1,i+1,max);
	//printf("f(%d,%d,%d)=%d\n",n,min,max,tot);
	return tot;
}
int main(){
	for(int i=0;i<=10;++i)
		printf("f(%d,1,6)=%d\n",i,foo(i,1,6));
	return 0;
}

