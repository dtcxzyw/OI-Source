#include <cstdio>
int cnt[1000000]={};
int main(){
	int n,x,fac=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&x);
		if(x>fac)fac=x;
		for(int j=1;j*j<=x;++j)
			if(x%j==0){
				++cnt[j];
				if(j*j!=x)++cnt[x/j];
			}
	}
	for(int i=1;i<=n;++i){
		while(cnt[fac]<i)--fac;
		printf("%d\n",fac);
	}
	return 0;
}

