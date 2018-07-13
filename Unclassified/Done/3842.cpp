#include <cstdio>
#include <cmath>
struct Line{
	int l,r;
	int move(int pos) const{
		if(l<=pos && pos<=r)return pos;
		else if(pos<l)return l;
		else return r;
	}
};
int main(){
	int n;
	scanf("%d",&n);
	Line line;
	int p=1;
	long long len=n-1;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&line.l,&line.r);
		int now=line.move(p);
		printf("to %d %d\n",i,now);
		len+=std::abs(now-p);
		p=now;
	}
	len+=std::abs(p-n);
	printf("%lld\n",len);
	return 0;
}

