#include <cstdio>
#include <algorithm>
struct Cow{
	int t,w;
	bool operator<(Cow rhs) const{
		return t==rhs.t?w>rhs.w:t<rhs.t;
	}
} cow[10000];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&cow[i].w,&cow[i].t);
	std::sort(cow,cow+n);
	int ans=0,t=0;
	for(int i=0;i<n;++i)
		if(cow[i].t==t)continue;
		else{
			ans+=cow[i].w;
			t=cow[i].t;
		}

	printf("%d\n",ans);
	return 0;
}

