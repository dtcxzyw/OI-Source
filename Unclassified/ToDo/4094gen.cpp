#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
int random(int x){
	return 1LL*rand()*rand()%x+1;
}
int main(){
	srand(clock());
	int n=100000;
	int m=10000;
	freopen("test.in","w",stdout);
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;++i)
		putchar('a'+rand()%26);
	puts("");
	for(int i=1;i<=m;++i){
		int a=random(n);
		int b=random(n);
		if(a>b)std::swap(a,b);
		int c=random(n);
		int d=random(n);
		if(c>d)std::swap(c,d);
		printf("%d %d %d %d\n",a,b,c,d);
	}
	return 0;
}

