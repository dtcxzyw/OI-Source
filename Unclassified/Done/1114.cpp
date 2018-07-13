#include <cstdio>
int head[200010]={};
int main(){
	int n;
	scanf("%d",&n);
	int d=100000,x,ans=0;
	head[d]=1;
	for(int i=2;i<=n+1;++i){
		scanf("%d",&x);
		d+=(x?1:-1);
		if(head[d]){
			if(ans<i-head[d])
				ans=i-head[d];
		}
		else head[d]=i;
	}
	printf("%d\n",ans);
	return 0;
}

