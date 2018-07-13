#include <cstdio>
const int size=1000001;
int sum[size]={},a[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	int c,x,y;
	for(int i=0;i<m;++i){
		scanf("%d%d",&c,&x);
		if(c==1){
			scanf("%d",&y);
			sum[x]+=y;
		}
		else{
			int ans=a[x];
			for(int i=1;i*i<=x;++i)
				if(!(x%i))
					ans+=sum[i]+(i*i!=x?sum[x/i]:0);
			printf("%d\n",ans);
		}
	}
	return 0;
}

