#include <cstdio>
#include <algorithm>
const int size=30005;
char buf[size];
const int a=127,b=823,c=577,d=347;
long long L[205],R[205],A[205][size];
int main(){
	int n,l,s;
	scanf("%d%d%d",&n,&l,&s);
	for(int i=0;i<n;++i){
		scanf("%s",buf+1);
		for(int j=1;j<=l;++j)L[j]=L[j-1]*a+buf[j];
		for(int j=l;j>=1;--j)R[j]=R[j+1]*b+buf[j];
		for(int j=1;j<=l;++j)A[j][i]=L[j-1]*c+R[j+1]*d;
	}
	long long res=0;
	for(int i=1;i<=l;++i){
		std::sort(A[i],A[i]+n);
		long long cur=1LL<<60,cnt=0;
		for(int j=0;j<=n;++j)
			if(A[i][j]==cur)++cnt;
			else{
				res+=cnt*(cnt-1)>>1;
				cur=A[i][j];
				cnt=1;
			}
	}
	printf("%d\n",res);
	return 0;
}

