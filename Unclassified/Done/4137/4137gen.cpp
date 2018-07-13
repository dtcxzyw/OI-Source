#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
const int size=2000;
int random(){
	return rand()%size;
}
int main(){
	srand(time(0));
	freopen("test.in","w",stdout);
	int n=size;
	int m=size*2;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;++i)
		printf("%d ",random()%40);
	puts("");
	for(int i=1;i<=m;++i){
		int l=random()+1;
		int r=random()+1;
		if(l>r)std::swap(l,r);
		printf("%d %d\n",l,r);
	}
	return 0;
}

