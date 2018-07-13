#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int random(int x){
	return 1LL*rand()*rand()%x+1;
}
int main(){
	srand(clock());
	freopen("test.in","w",stdout);
	int n=200000;
	int m=500000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;++i)
		printf("%d ",rand());
	puts("");
	for(int i=0;i<m;++i){
		if(rand()%5){
			int l=random(n);
			int r=random(n);
			if(l>r)std::swap(l,r);
			printf("2 %d %d\n",l,r);
		}
		else{
			printf("1 %d %d %d\n",random(n),random(n),random(1000000007));
		}
	}
	return 0;
}

