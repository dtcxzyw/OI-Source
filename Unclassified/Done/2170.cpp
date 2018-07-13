#include <cstdio>
const int size=20001;
int fa[size],cnt[size];
bool dp[size]={};
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
		fa[i]=i,cnt[i]=1;
	int u,v;
	for(int i=0;i<k;++i){
		scanf("%d%d",&u,&v);
		int fu=find(u),fv=find(v);
		if(fu!=fv){
			fa[fu]=fv;
			cnt[fv]+=cnt[fu];
		}
	}
	dp[0]=true;
	for(int i=1;i<=n;++i)
		if(find(i)==i)
			for(int j=n;j>=cnt[i];--j)
				dp[j]|=dp[j-cnt[i]];
	int pi=0,ni=0;
	for(int i=m;i>=1;--i)if(dp[i]){pi=i;break;}
	for(int i=m;i<=n;++i)if(dp[i]){ni=i;break;}
	if(m-pi<=ni-m)printf("%d\n",pi);
	else printf("%d\n",ni);
	return 0;
}

