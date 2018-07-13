#include <cstdio>
int lowbit(int x){
	while(x%10==0)x/=10;
	return x%10;
}
int powm(int a,int k){
	int res=1;
	while(k){
		if(k&1)res=res*a%10;
		k>>=1,a=a*a%10;
	}
	return res;
}
int main(){
	int n,x=1,y,c2=0,c5=0;
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		y=i;
		while(!(y&1))y>>=1,++c2;
		while(y%5==0)y/=5,++c5;
		x=x*y%10;
	}
	if(c2>c5)x=x*powm(2,c2-c5)%10;
	else x=x*powm(5,c5-c2)%10;
	printf("%d\n",x);
	return 0;
}

