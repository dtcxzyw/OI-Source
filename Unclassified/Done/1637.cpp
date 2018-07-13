#include <cstdio>
#include <algorithm>
#include <cstring>
const int size=30010;
long long input[size],map[size];
int cnt[size],siz,l[size];
void add(int i){
	while(i<=siz){
		++cnt[i];
		i+=i&-i;
	}
}
int query(int i){
	int ans=0;
	while(i){
		ans+=cnt[i];
		i-=i&-i;
	}
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%lld",&input[i]);
	memcpy(map,input,sizeof(long long)*n);
	std::sort(map,map+n);
	siz=std::unique(map,map+n)-map;
	for(int i=0;i<n;++i)
		input[i]=std::lower_bound(map,map+siz,input[i])-map+1;
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;++i){
		l[i]=query(input[i]-1);
		add(input[i]);
	}
	memset(cnt,0,sizeof(cnt));
	long long ans=0;
	for(int i=n-1;i>=0;--i){
		ans+=l[i]*((n-i-1)-query(input[i]));
		add(input[i]);
	}
	printf("%lld\n",ans);
	return 0;
}

