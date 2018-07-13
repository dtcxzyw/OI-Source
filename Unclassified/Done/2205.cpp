#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int size=100010;
int pos[size],map[size<<1],cnt[size]={},id[size];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	int off;
	char c[2];
	pos[0]=0;
	for(int i=1;i<=n;++i){
		scanf("%d%s",&off,c);
		pos[i]=pos[i-1]+(*c=='L'?-off:off);
	}
	memcpy(map,pos,sizeof(pos));
	sort(map,map+n+1);
	int siz=unique(map,map+n+1)-map;
	for(int i=0;i<=n;++i)
		id[i]=lower_bound(map,map+siz,pos[i])-map;
	for(int i=1;i<=n;++i){
		int l=id[i-1],r=id[i];
		if(l>r)std::swap(l,r);
		++cnt[l],--cnt[r];
	}
	for(int i=1;i<=siz;++i)
		cnt[i]+=cnt[i-1];
	int ans=0;
	for(int i=0;i<siz-1;++i){
		if(cnt[i]>=k)
			ans+=map[i+1]-map[i];
	}
	printf("%d\n",ans);
	return 0;
}

