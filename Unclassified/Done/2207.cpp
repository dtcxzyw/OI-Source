#include <cstdio>
#include <algorithm>
int A[1000][2],B[5000],C[5000];
bool p[4005][4005];
int main(){
	int n,k,cnt=0;
	scanf("%d%d",&n,&k);
	int a,b;
	for(int i=0;i<k;++i){
		scanf("%d%d",&a,&b);
		B[cnt++]=A[i][0]=a;
		B[cnt++]=A[i][1]=b;
	}
	std::sort(B,B+cnt);
	int siz=std::unique(B,B+cnt)-B;
	for(int i=1;i<siz;++i)
		if(B[i]-B[i-1]>2)
			B[cnt++]=B[i]-1;
	B[cnt++]=1;
	B[cnt++]=n;
	std::sort(B,B+cnt);
	siz=std::unique(B,B+cnt)-B;
	for(int i=0;i<k;++i){
		int l=std::lower_bound(B,B+siz,A[i][0])-B;
		int r=std::lower_bound(B,B+siz,A[i][1])-B;
		p[l][r]=p[r][l]=true;
	}
	int ans=1;
	cnt=0;
	for(int i=0;i<siz;++i){
		bool flag=true;
		for(int j=0;j<cnt;++j)
			if(p[C[j]][i]){
				flag=false;
				break;
			}
		if(flag)C[cnt++]=i;
		else cnt=1,C[0]=i,++ans;
	}
	printf("%d\n",ans);
	return 0;
}

