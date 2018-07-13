#include <cstdio>
int sum[151][151]={};
char buf[160];
int query(int bx,int by,int ex,int ey){
	return sum[ex][ey]-sum[ex][by]-sum[bx][ey]+sum[bx][by];
}
int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",buf+1);
		for(int j=1;j<=n;++j)
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+(buf[j]=='W');
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			for(int k=i+1;k<=n;++k)
				for(int l=j+1;l<=n;++l)
					ans+=(query(i,j,k,l)==(k-i)*(l-j));
	printf("%d\n",ans);
	return 0;
}

