#include <cstdio>
#include <cstdint>
int p,inv[3000001];
int main(){
	int n;
	scanf("%d%d",&n,&p);
	inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=static_cast<int64_t>(p-p/i)*inv[p%i]%p;
	for(int i=1;i<=n;++i)
		printf("%d\n",inv[i]);
	return 0;
}

