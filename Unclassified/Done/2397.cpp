#include <cstdio>
int main(){
	int n,x,cnt=0,now;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&x);
		if(!cnt)now=x,cnt=1;
		if(now==x)++cnt;
		else --cnt;
	}
	printf("%d\n",now);
	return 0;
}

