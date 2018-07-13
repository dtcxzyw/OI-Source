#include <cstdio>
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int ans=1;
		for(int j=2;j<=i;++j)
			ans^=j;
		printf("%d %d\n",i,ans);
	}
	return 0;
}

