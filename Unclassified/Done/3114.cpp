#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
struct Line{
	int p,y;
	bool operator<(Line rhs) const{
		return p==rhs.p?y<rhs.y:p<rhs.p;
	}
} L[100002];
int main(){
	int n;
	scanf("%d",&n);
	int x,y,r;
	for(int i=0;i<n;++i){
		scanf("%d%d%d",&x,&y,&r);
		x*=-r;
		L[i<<1].p=x-r,L[i<<1].y=y;
		L[i<<1|1].p=x,L[i<<1|1].y=-y;
	}
	n<<=1;
	sort(L,L+n);
	set<int> Y,saw;
	for(int i=0;i<n;++i){
		for(int j=i;j<n && L[i].p==L[j].p;++j)
			if(L[j].y>0)Y.insert(L[j].y);
			else Y.erase(-L[j].y);
		if(Y.size())saw.insert(*Y.begin());
	}
	printf("%d\n",static_cast<int>(saw.size()));
	return 0;
}

