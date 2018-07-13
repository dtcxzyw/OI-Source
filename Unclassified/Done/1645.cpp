#include <cstdio>
#include <algorithm>
struct Range{
	int l,r,c;
	bool operator<(Range rhs) const{
		return r<rhs.r;
	}
} A[1000];
bool flag[1001]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d%d",&A[i].l,&A[i].r,&A[i].c);
	std::sort(A,A+n);
	int r=0,cnt=0;
	for(int i=0;i<n;++i){
		for(int j=A[i].l;j<=r;++j)A[i].c-=flag[j];
		r=A[i].r;
		for(int j=r;A[i].c>0;--j)
			if(!flag[j]){
				flag[j]=true;
				--A[i].c;
				++cnt;
			}
	}
	printf("%d\n",cnt);
	return 0;
}

