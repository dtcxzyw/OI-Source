#include <cstdio>
#include <cstring>
#include <algorithm>
int prime[50001];
bool flag[50001],mark[1000010];
int main(){
	int l,r,cnt=0;
	scanf("%d%d",&l,&r);
	l=std::max(2,l);
	int d=r-l+1;
	memset(flag,1,sizeof(flag));
	memset(mark,1,sizeof(mark));
	for(int i=2;1LL*i*i<=r;++i){
		if(flag[i]){
			prime[++cnt]=i;
			int begin=std::max(l,i)/i*i;
			if(begin<l || l<=i)begin+=i;
			for(int k=begin-l;k<d;k+=i)
				mark[k]=false;
		}
		for(int j=1;j<=cnt && 1LL*i*prime[j]<=50000LL;++j){
			flag[i*prime[j]]=false;
			if(!(i%prime[j]))break;
		}
	}
	int ans=0;
	for(int i=0;i<d;++i)
		ans+=mark[i];
	printf("%d\n",ans);
	return 0;
}

