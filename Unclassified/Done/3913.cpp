#include <cstdio>
#include <algorithm>
const int size=1000000;
int X[size],Y[size];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;++i)
		scanf("%d%d",&X[i],&Y[i]);
	std::sort(X,X+k),std::sort(Y,Y+k);
	int sx=std::unique(X,X+k)-X,
		sy=std::unique(Y,Y+k)-Y;
	long long w=n-sx,h=n-sy,S=1LL*n*n;
	printf("%lld\n",S-w*h);
	return 0;
}

