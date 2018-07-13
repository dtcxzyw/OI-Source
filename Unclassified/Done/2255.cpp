#include <cstdio>
#include <algorithm>
struct Range{
	int l,r;
	bool operator<(Range rhs) const{
		return r<rhs.r;
	}
} task[150];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&task[i].l,&task[i].r);
	std::sort(task,task+n);
	int l=0,r=0,cnt=0;
	for(int i=0;i<n;++i)
	if(task[i].l>=std::min(l,r)){
		++cnt;
		if(task[i].l>=l && task[i].l>=r){
			if(l<r)r=task[i].r;
			else l=task[i].r;
		}
		else if(task[i].l>=l)l=task[i].r;
		else r=task[i].r;
	}
	printf("%d\n",cnt);
	return 0;
}

