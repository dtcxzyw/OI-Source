#include <cstdio>
#include <algorithm>
const int size=20;
int h[size],w[size],c[size],dph[1<<size],dpw[1<<size];
int main(){
	int n,H;
	scanf("%d%d",&n,&H);
	for(int i=0;i<n;++i)
		scanf("%d%d%d",&h[i],&c[i],&w[i]);
	int end=1<<n,ans=-1;
	dph[0]=0;
	dpw[0]=1<<30;
	for(int i=1;i<end;++i){
		for(int j=0;j<n;++j)
			if(i&(1<<j)){
				int src=i^(1<<j);
				if(dpw[src]<c[j])continue;
				dph[i]=dph[src]+h[j];
				dpw[i]=std::max(dpw[i],std::min(dpw[src]-c[j],w[j]));
			}
		if(dph[i]>=H && dpw[i]>ans)ans=dpw[i];
	}
	if(ans<0)puts("Mark is too tall");
	else printf("%d\n",ans);
	return 0;
}

