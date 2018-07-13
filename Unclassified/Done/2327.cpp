#include <cstdio>
int A[10001],f[10001];
int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&A[i]);
	for(int b=0;b<=1;++b){
		f[1]=b;
		f[2]=A[1]-f[1];
		bool flag=true;
		for(int i=3;i<=n;++i){
			f[i]=A[i-1]-f[i-1]-f[i-2];
			if(f[i]!=0 && f[i]!=1){
				flag=false;
				break;
			}
		}
		if(A[n]==f[n]+f[n-1])ans+=flag;
	}
	printf("%d\n",ans);
	return 0;
}

